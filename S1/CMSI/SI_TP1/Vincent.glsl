const int Steps = 1000;
const float Epsilon = 0.01; // Marching epsilon
const float T=0.5;
const int noctaves = 6;

const float rB=50.0; // Maximum

// Transforms
// p : point
// a : angle of rotation
vec3 rotateY(vec3 p, float a)
{
   // return p;
   mat3 Ry;
   Ry[0] = vec3( cos(a), 0, sin(a));
   Ry[1] = vec3(      0, 1,      0);
   Ry[2] = vec3(-sin(a), 0, cos(a));
   return Ry * p;
}

// Smooth falloff function
// r : small radius
// R : Large radius
float falloff( float r, float R )
{
   float x = clamp(r/R,0.0,1.0);
   float y = (1.0-x*x);
   return y*y*y;
}

// Primitive functions

// Point skeleton
// p : point
// c : center of skeleton
// e : energy associated to skeleton
// R : large radius
float point(vec3 p, vec3 c, float e,float R)
{
   return e*falloff(length(p-c),R);
}


// Blending
// a : field function of left sub-tree
// b : field function of right sub-tree
float Blend(float a,float b)
{
   return a+b;
}

vec2 hash( vec2 p ) 
{
	p = vec2( dot(p,vec2(127.1,311.7)),
			  dot(p,vec2(269.5,183.3)) );

	return -1.0 + 2.0*fract(sin(p)*43758.5453123);
}

float noise( in vec2 p )
{
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;

	vec2 i = floor( p + (p.x+p.y)*K1 );
	
    vec2 a = p - i + (i.x+i.y)*K2;
    vec2 o = step(a.yx,a.xy);    
    vec2 b = a - o + K2;
	vec2 c = a - 1.0 + 2.0*K2;

    vec3 h = max( 0.5-vec3(dot(a,a), dot(b,b), dot(c,c) ), 0.0 );

	vec3 n = h*h*h*h*vec3( dot(a,hash(i+0.0)), dot(b,hash(i+o)), dot(c,hash(i+1.0)));

    return dot( n, vec3(70.0) );
}

float turbulence(in vec2 p, in float amplitude, in float fbase, in float attenuation, in int noctave) {
    int i;
    float res = .0;
    float f = fbase;
    for (i=0;i<noctave;i++) {
        res = res+amplitude*noise(f*p);
        amplitude = amplitude*attenuation;
        f = f*2.;
    }
    return res;
}

float ridged(in vec2 p) {
    return 2.0*(0.5-abs(0.5-turbulence(p, 0.4, 0.2, 0.5, noctaves)));
}

float Terrain(in vec3 p)
{
    float altitude = ridged(p.xz);
    return altitude; 
}

float Water(in vec3 p)
{
    float waterLevel = -0.1 -0.1 * cos(0.5*iTime);
    waterLevel += 0.002*noise(p.xz);
    return waterLevel;
}

// Potential field of the object
// p : point
float object(vec3 p)
{
   return max(Terrain(p), Water(p)) - p.y;
}

// Calculate object normal
// p : point
vec3 ObjectNormal(in vec3 p )
{
   float eps = 0.0001;
   vec3 n;
   float v = object(p);
   n.x = object( vec3(p.x+eps, p.y, p.z) ) - v;
   n.y = object( vec3(p.x, p.y+eps, p.z) ) - v;
   n.z = object( vec3(p.x, p.y, p.z+eps) ) - v;
   return normalize(n);
}

// Trace ray using ray marching
// o : ray origin
// u : ray direction
// rA: minimum ray marching distance from origin
// h : hit
// s : Number of steps
float Trace(vec3 o, vec3 u, float rA, out bool h,out int s)
{
   h = false;

   // Don't start at the origin
   // instead move a little bit forward
   float t=rA;

   for(int i=0; i<Steps; i++)
   {
      s=i;
      vec3 p = o+t*u;
      float v = object(p);
      // Hit object (1) 
      if (v > 0.0)
      {
         s=i;
         h = true;
         break;
      }
      // Move along ray
      t += max(Epsilon,-v/2.0);  

      // Escape marched far away
      if (t>rB)
      {
         break;
      }
   }
   return t;
}

// Background color
vec3 background(vec3 rd)
{
   return mix(vec3(0.5, 0.5, 0.6), vec3(254.0/255.0,194.0/255.0,104.0/255.0), -rd.y*1.0+0.3);
}

// Shading and lighting
// p : point,
// n : normal at point
// s : number of steps
// u : direction of ray
vec3 ShadeWithoutWater(vec3 p, vec3 n, int s, vec3 u)
{
   // point light
   const vec3 lightPos = vec3(5.0, 5.0, 5.0);
   const vec3 lightColor = vec3(254.0/255.0,194.0/255.0,104.0/255.0);

   vec3 l = normalize(lightPos - p);

   // Not even Phong shading, use weighted cosine instead for smooth transitions
   float diff = 0.5*(1.0+dot(n, l));

   vec3 c =  0.5*vec3(0.5,0.5,0.5)+0.5*diff*lightColor;
   float fog = 0.7*float(s)/(float(Steps-1));
   c = (1.0-fog)*c+fog*vec3(1.0,1.0,1.0);



   // colour depending on altitude y
   float max_y = 0.4;
   float max_whitening = 0.3;
   vec3 whitening = vec3(0.8*(p.y-max_y)+max_whitening+0.03, 
       0.9*(p.y-max_y)+max_whitening, 
       1.0*(p.y-max_y)+max_whitening); 
   c += whitening;
   
   
   
   // contour lines
   // if (mod(p.y, 0.1) < 0.01) return c/2.0;
   
   c -= turbulence(p.xz, 0.2, 0.5, 0.7, 10);
   
   return c;
}

// raytracing to get color of a pixel
vec3 getPixelColorAfterReflection(vec3 ro,vec3 rd)
{
   bool hit; // Trace ray
   int s; // Number of steps

   float t = Trace(ro, rd, 0.0, hit,s);
   vec3 pos=ro+t*rd;
   // Shade background
   vec3 rgb = background(rd);

   if (hit)
   {
      // Compute normal
      vec3 n = ObjectNormal(pos);

      // Shade object with light
      rgb = ShadeWithoutWater(pos, n, s, rd);
   }
   return rgb;
}


// Shading and lighting
// p : point,
// n : normal at point
// s : number of steps
// u : direction of ray
vec3 ShadeWithWater(vec3 p, vec3 n, int s, vec3 u)
{
   vec3 c; // rgb color vector forward declaration 
    
   // calculate water level
   float waterLevel = Water(p);
   
   // shade mountains
   if (p.y > waterLevel)
       return ShadeWithoutWater(p, n, s, u);
   
   
   // shade water
   p.y = waterLevel; // avoid immidiate hit with water surface
   // n += 0.005*noise(p.xz);
   vec3 r = getPixelColorAfterReflection(p, reflect(u, n)); // color of point that reflects in water
   vec3 w = vec3(195.0/256.0, 242.0/256.0, 255.0/256.0); // water color
   c = 0.7*r + 0.3*w;
   
   c -= turbulence(p.xz, 0.2, 0.5, 0.7, 10);
   
   return c;
}

// raytracing to get color of a pixel
vec3 getPixelColor(vec3 ro,vec3 rd)
{
   bool hit; // Trace ray
   int s; // Number of steps

   float t = Trace(ro, rd, 1.0, hit,s);
   vec3 pos=ro+t*rd;
   // Shade background
   vec3 rgb = background(rd);

   if (hit)
   {
      // Compute normal
      vec3 n = ObjectNormal(pos);

      // Shade object with light
      rgb = ShadeWithWater(pos, n, s, rd);
   }
   return rgb;
}


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
   vec2 pixel = (gl_FragCoord.xy / iResolution.xy)*2.0-1.0; // screen values in [-1.0|+1.0]

   // compute ray origin and direction
   float asp = iResolution.x / iResolution.y; // aspect ratio of screen
   vec3 rd = vec3(asp*pixel.x, pixel.y-0.3, -4.0); // ray
   vec3 ro = vec3(0.0, 1.5, 15.0); // viewpoint

   vec2 mouse = iMouse.xy / iResolution.xy;
   //float a=-mouse.x;
   float a= iTime*0.1;
   rd.z = rd.z+2.0*mouse.y;
   rd = normalize(rd);
   ro = rotateY(ro, a);
   rd = rotateY(rd, a);


   vec3 rgb = getPixelColor(ro, rd);

   fragColor=vec4(rgb, 1.0);
}
