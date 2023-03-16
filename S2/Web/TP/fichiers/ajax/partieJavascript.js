//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

let xmlDoc = chargerHttpXML("../countriesTP.xml");
let worldMapDoc = chargerHttpXML("worldHigh.svg");

let countryCodes = xmlDoc.getElementsByTagName("cca2");

function recupererPremierEnfantDeTypeElement(n) {
    let x = n.firstChild;
    while (x.nodeType != 1) { // Test if x is an element node (and not a text node or other)
        x = x.nextSibling;
    }
    return x;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//change le contenu de l'�lement avec l'id "nom" avec la chaine de caract�res en param�tre	  
function setNom(nom) {
    let elementHtmlARemplir = window.document.getElementById("id_nom_a_remplacer");
    elementHtmlARemplir.innerHTML = nom;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//charge le fichier XML se trouvant � l'URL relative donn� dans le param�treet le retourne
function chargerHttpXML(xmlDocumentUrl) {

    let httpAjax;

    httpAjax = window.XMLHttpRequest ?
        new XMLHttpRequest() :
        new ActiveXObject('Microsoft.XMLHTTP');

    if (httpAjax.overrideMimeType) {
        httpAjax.overrideMimeType('text/xml');
    }

    //chargement du fichier XML � l'aide de XMLHttpRequest synchrone (le 3� param�tre est d�fini � false)
    httpAjax.open('GET', xmlDocumentUrl, false);
    httpAjax.send();

    return httpAjax.responseXML;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// Charge le fichier JSON se trouvant � l'URL donn�e en param�tre et le retourne
function chargerHttpJSON(jsonDocumentUrl) {

    let httpAjax;

    httpAjax = window.XMLHttpRequest ?
        new XMLHttpRequest() :
        new ActiveXObject('Microsoft.XMLHTTP');

    if (httpAjax.overrideMimeType) {
        httpAjax.overrideMimeType('text/json');
    }

    // chargement du fichier JSON � l'aide de XMLHttpRequest synchrone (le 3� param�tre est d�fini � false)
    httpAjax.open('GET', jsonDocumentUrl, false);
    httpAjax.send();

    let responseData = eval("(" + httpAjax.responseText + ")");

    return responseData;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function Button1_function(){
    document.getElementById("myButton1").style.color = 'white';
    changeBackground('blue');

}
function changeBackground(color){
    document.body.style.background = color;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Button2_function(){
    document.getElementById("myButton1").style.color = 'black';
    changeBackground('white');
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Bouton3_cherchePays(xmlDocumentUrl, xslDocumentUrl, countryCode ,baliseElementARecuperer) {

    // Chargement du fichier XSL � l'aide de XMLHttpRequest synchrone 
    let xslDocument = chargerHttpXML(xslDocumentUrl);

    //création d'un processuer XSL
    let xsltProcessor = new XSLTProcessor();

    // Importation du .xsl
    xsltProcessor.importStylesheet(xslDocument);

    //passage du param�tre � la feuille de style
    xsltProcessor.setParameter("", "code",countryCode);

    // Chargement du fichier XML � l'aide de XMLHttpRequest synchrone 
    let xmlDocument = chargerHttpXML(xmlDocumentUrl);

    // Cr�ation du document XML transform� par le XSL
    let newXmlDocument = xsltProcessor.transformToDocument(xmlDocument);

    // Recherche du parent (dont l'id est "here") de l'�l�ment � remplacer dans le document HTML courant
    let elementHtmlParent = window.document.getElementById("pays_a_chercher");

    // ins�rer l'�lement transform� dans la page html
    elementHtmlParent.innerHTML=newXmlDocument.getElementsByTagName(baliseElementARecuperer)[0].innerHTML;

    if(mapLoaded){
        colorCountry(countryCode);
    }

}

function colorCountry(countryCode){


    let mapContainer = document.getElementById("worldMapContainer");
    let mapSVG = mapContainer.children[0];

    let countryList = mapSVG.getElementsByTagName("g")[0].children;

    // On recolorie les pays à leur couleur d'origine
    let countries = mapSVG.querySelectorAll(".land");
    countries.forEach(function(country) {
        country.style.fill = "#cccccc";
    });

    let xmlDoc = chargerHttpXML("../countriesTP.xml");


    // On récupère le cca2 dans le doute (si l'utilisateur entre le callingCode ou un autre code au lieu du cca2)
    let xpath = `//country[country_codes/* = '${countryCode.toUpperCase()}']/country_codes/cca2`;
    let cca2 = xmlDoc.evaluate(xpath , xmlDoc , null , XPathResult.STRING_TYPE , null ).stringValue;

    if( cca2 === '' ){
        xpath = `//country[callingCode = '${countryCode}']/country_codes/cca2`;
        cca2 =  xmlDoc.evaluate(xpath , xmlDoc , null , XPathResult.STRING_TYPE , null ).stringValue;
    }

    // Récupération des langages du pays
    xpath = `//country[country_codes/cca2 = '${cca2}']/languages/*`;
    let langList = xmlDoc.evaluate(xpath , xmlDoc, null , XPathResult.ANY_TYPE, null);


    let lang = langList.iterateNext();

    while(lang){
        // On récupère les cca2 des pays qui parlent les mêmes langues
        xpath = `//country[languages/* = '${lang.textContent}']/country_codes/cca2`;

        let matchList = xmlDoc.evaluate(xpath , xmlDoc, null , XPathResult.ANY_TYPE , null);

        // Then on colorie en vert les pays qui parlent la même langue
        let match = matchList.iterateNext();

        while(match){
            if( mapSVG.getElementById(match.textContent) != null ){
                mapSVG.getElementById(match.textContent).style.fill = 'green';
            }

            match = matchList.iterateNext();
        }

        lang = langList.iterateNext();

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Bouton4_loadSvg(svgDocumentUrl){

    let svg = document.getElementById('exemple');

    let s = chargerHttpXML(svgDocumentUrl);

    let serializer = new XMLSerializer();

    svg.innerHTML = serializer.serializeToString(s);
}

function makeSvgClickable(svgElementId , elementToReplace , attributeToDisplay){

    let elements = document.getElementById(svgElementId).children[0].children;

    for(let i = 0 ; i < elements.length ; i++){
        elements[i].addEventListener('click', function(){
            document.getElementById(elementToReplace).innerHTML = this.getAttribute(attributeToDisplay);
        });
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
let mapLoaded = false;
function Bouton6_afficherCarte(svgDocumentUrl) {

    let svg = document.getElementById('worldMapContainer');

    svg.setAttribute("align","center");

    svg.setAttribute("class" , "map");

    let s = chargerHttpXML(svgDocumentUrl);

    let serializer = new XMLSerializer();

    svg.innerHTML = serializer.serializeToString(s);

    mapLoaded = true;
}

function Bouton7_makeCountriesClickable(){

    mapClickable = true;

    let countries = document.getElementById('worldMapContainer').children[0].getElementsByTagName('g')[0].children;

    for( let i = 0 ; i < countries.length ; i++ ){

        countries[i].addEventListener('click', function(){
            document.getElementById('countryNameDisplay').innerHTML = this.getAttribute('countryname');
        });
    }

}

function captureMouseMovement(){

    // Chargement du document xml
    const xmlDoc = '../countriesTP.xml';

    let countries = document.getElementById('worldMapContainer').children[0].getElementsByTagName('g')[0].children;

    for(let i = 0 ; i < countries.length ; i++){
        // On save la couleur d'avant pour ne pas perdre le formatage eventuel
        let previousColor = countries[i].style.fill;

        countries[i].addEventListener('mouseover' , mouseOver)

        countries[i].addEventListener('mouseleave', function() {
            this.style.fill = previousColor;
            infoBubble.style.display = "none";
        })
    }

}


let infoBubble = document.createElement("div");
infoBubble.setAttribute("id", "infoBubble");
infoBubble.style.display = "none";
window.onload = () => {document.body.appendChild(infoBubble)};

let showCurrency = false;
let showTemperature = false;
let inGame = false;


async function mouseOver() {

    /// Partie changement de couleur
    // Si le pays est en vert , on rend la couleur plus foncée
    if(this.style.fill === 'green'){
        this.style.fill = "#556B2F";
    }
    else if(this.style.fill !== 'red' && this.style.fill !== 'blue'){
        // Sinon on met une couleur qui montre qu'on l'a selectionné
        this.style.fill ='#404040';
    }

    const countryCode = this.getAttribute('id');

    const countryName = this.getAttribute('countryname');

    //Récuperation de la capitale du pays
    let xpath = `//country[country_codes/cca2 = '${countryCode}' ]/capital`;
    const capital = xmlDoc.evaluate(xpath, xmlDoc , null , XPathResult.STRING_TYPE, null).stringValue;

    //Récupération des langues du pays
    xpath = `//country[country_codes/cca2 = '${countryCode}' ]/languages`;
    const languageList = xmlDoc.evaluate(xpath , xmlDoc , null, XPathResult.ANY_TYPE, null);

    //On crée un string avec les langues
    let lang = languageList.iterateNext();
    let languages = "";

    while(lang){
        languages += `${lang.textContent}`;
        lang = languageList.iterateNext();
    }

    //Récupération du drapeau du pays
    let flag = 'http://www.geonames.org/flags/x/' + countryCode.toLowerCase() + '.gif';

    //Si le bouton 10 est clické, on récupère la monnaie du pays aussi
    if(showCurrency){
        let currency =  'https://restcountries.com/v2/alpha/' + countryCode.toLowerCase();

        // On charge le fichier JSON contenu dans l'url
        let jsonFile = chargerHttpJSON(currency);

        var currencyName = jsonFile.currencies[0].name;
    }

    if(showTemperature){

        var temp = await getTemperatureForCountry(countryCode);
    }

    // Update the infoBubble content
    infoBubble.innerHTML = `
    <div class="infoBubble__content">
      <div class="infoBubble__country">${countryName}</div>
      <div class="infoBubble__capital"><span>Capital:</span> ${capital}</div>
      <div class="infoBubble__languages"><span>Languages:</span> ${languages}</div>
      ${showCurrency ? `<div class="infoBubble__currency"><span>Currency:</span> ${currencyName}</div>` : ''}
      ${showTemperature ?`<div class="infoBubble__temperature"><span>Temperature:</span> ${temp}°C</div>` : ''}
      <div class="infoBubble__flag"><img src="${flag}" width="50" alt=""></div>
    </div>
  `;

    // Show the infoBubble
    if( !inGame ){
        infoBubble.style.display = "block";
    }

    document.addEventListener('mousemove', (event) => {
        infoBubble.style.left = `${event.pageX + 10}px`;
        infoBubble.style.top = `${event.pageY - 10}px`;
    });

}



function Bouton9_addAutoComplete(){
    let autoComplete = document.getElementById("myButton9");

    autoComplete.style.backgroundColor = '#556B2F';

    autoComplete.textContent = "Autocomplete activé";

    const inputField = document.getElementById("codePays");

    const button = document.getElementById("myButton9");

    const parser = new DOMParser();

    // On récupère tous les CCA2 des pays
    const xpath = "//country/country_codes/cca2";

    const nodes = xmlDoc.evaluate(xpath, xmlDoc, null, XPathResult.ANY_TYPE, null);

    const options = [];

    // Adding the options from the XML file to the array options
    let node = nodes.iterateNext();
    while (node) {
        options.push(node.textContent);
        node = nodes.iterateNext();
    }

    // Création de la datalist
    const datalist = document.createElement("datalist");
    datalist.id = "autoComplete";

    // On rajoute les options du tablea options à la datalist
    for( let option in options ){
        const optionElement = document.createElement("option");

        optionElement.setAttribute("value", options[option] );
        datalist.appendChild(optionElement);
    }

    // On rajoute la datalist à notre document
    inputField.appendChild(datalist);

    // On lie l'input et la datalist
    inputField.setAttribute("list" , datalist.id);

}


function Bouton10_addCurrency(){
    showCurrency = true;
}


// Retourne le nom d'un pays aléatoire
function getRandomCountryCode(){

    const randomCountryCode = countryCodes[Math.floor(Math.random() * countryCodes.length)].textContent;

    return randomCountryCode;

}

function getCountryNameFromCode( countryCode ){

    let xpath = `//country[country_codes/cca2 = '${countryCode}']/country_name/common_name`;

    return xmlDoc.evaluate( xpath, xmlDoc, null, XPathResult.STRING_TYPE, null).stringValue;
}

function getCountryCapitalFromCode ( countryCode ){
    let xpath = `//country[country_codes/cca2 = '${countryCode}']/capital`;

    return xmlDoc.evaluate( xpath, xmlDoc, null, XPathResult.STRING_TYPE, null).stringValue;
}

let mapClickable = false;

function clearColors(){
    let worldMapSVG = document.getElementById("worldMapContainer").children[0];

    let countriesPaths = worldMapSVG.getElementsByTagName("path");

    for (let country of countriesPaths ){
        country.style.fill = "#CCCCCC";
    }

}
function Bouton12_geoGuessr(){

    // Si la carte n'est pas chargée, on epargne la galère à l'utilisateur
    if( !mapLoaded ){
        document.getElementById("myButton6").click();
    }

    clearColors();

    inGame = true;

    document.getElementById("myButton7").click();

    let countryToSearch = getCountryNameFromCode( getRandomCountryCode() );

    let gameState = document.getElementById("countryToSearch");

    let gameEnd = false;

    gameState.innerHTML = "Country to find : " + countryToSearch;

    let worldMapSVG = document.getElementById("worldMapContainer").children[0];

    let countriesPaths = worldMapSVG.getElementsByTagName("path");

    let attemptNumber = 0;

    console.log(countriesPaths);
    for ( let country of countriesPaths ){

        country.addEventListener('mouseover' , mouseOver);


        country.addEventListener('mouseleave', function() {
            if(this.style.fill !== 'red' && this.style.fill !== 'blue'){
                this.style.fill = '';
            }
            infoBubble.style.display = "none";
        });


        country.addEventListener('click' , function() {

            attemptNumber++;

            const userAttempt = getCountryNameFromCode(this.getAttribute("id"));

            console.log("country clicked");

            if(userAttempt === countryToSearch){
                //gameState.innerHTML = "NICE , you found " + countryToSearch + " in " + attemptNumber + " attempts ! ";
                alert(`Nice job , you found '${countryToSearch} in ${attemptNumber} attempts :)`);
                this.style.fill = "blue";
                clearColors();
                gameState.innerHTML = '';
                inGame = false;
                gameEnd = true;
                return;
            }else{
                this.style.fill = "red";
            }
        });
    }

    if(gameEnd === true){
        return;
    }
}

// On capture la temperature de chaque pays grace à l'API openWeather
// L'api n'utilisant pas la m
async function getTemperatureForCountry(countryCode) {
    const apiKey = 'db022c2a0c5a4108bfb93433231603';
    const apiUrl = `http://api.weatherapi.com/v1/current.json?key=${apiKey}&q=${getCountryCapitalFromCode(countryCode)}`;
    try {
        const response = await fetch(apiUrl);
        const data = await response.json();
        if (!data.current) {
            console.error(`No temperature data available for this country. ${getCountryNameFromCode(countryCode)}`);
            return;
        }
        return data.current.temp_c;
    } catch (error) {
        console.error(error);
        console.error(`Error fetching temperature data for this country. ${getCountryNameFromCode(countryCode)}`);
    }
}


async function Bouton13_showTemperatures(){

    if(!mapLoaded){
        document.getElementById("myButton6").click();
    }

    showTemperature = true;

    let worldMapSVG = document.getElementById("worldMapContainer").children[0];

    const countriesPaths = worldMapSVG.querySelectorAll('.land');
    const colors = ['#add8e6', '#f29b9b', '#e86f6f', '#d64545', '#b61818' , 'black'];
    const colorIndexByTemp = (temp) => {
        if (temp == null) return 5;
        if (temp < 0) return 0;
        if (temp < 10) return 1;
        if (temp < 20) return 2;
        if (temp < 30) return 3;
        return 4;
    };

    for (let country of countriesPaths) {
        const countryCode = country.getAttribute('id');

        const temp = await getTemperatureForCountry(countryCode);

        const colorIndex = colorIndexByTemp(temp);

        country.style.fill = colors[colorIndex];

        country.addEventListener('click', function() {
            const countryName = getCountryNameFromCode(countryCode);
            document.getElementById('countryNameDisplay').textContent = countryName;
        });
    }

    captureMouseMovement();


}








