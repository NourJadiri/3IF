//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function recupererPremierEnfantDeTypeElement(n) {
    var x = n.firstChild;
    while (x.nodeType != 1) { // Test if x is an element node (and not a text node or other)
        x = x.nextSibling;
    }
    return x;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//change le contenu de l'�lement avec l'id "nom" avec la chaine de caract�res en param�tre	  
function setNom(nom) {
    var elementHtmlARemplir = window.document.getElementById("id_nom_a_remplacer");
    elementHtmlARemplir.innerHTML = nom;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//charge le fichier XML se trouvant � l'URL relative donn� dans le param�treet le retourne
function chargerHttpXML(xmlDocumentUrl) {

    var httpAjax;

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

    var httpAjax;

    httpAjax = window.XMLHttpRequest ?
        new XMLHttpRequest() :
        new ActiveXObject('Microsoft.XMLHTTP');

    if (httpAjax.overrideMimeType) {
        httpAjax.overrideMimeType('text/xml');
    }

    // chargement du fichier JSON � l'aide de XMLHttpRequest synchrone (le 3� param�tre est d�fini � false)
    httpAjax.open('GET', jsonDocumentUrl, false);
    httpAjax.send();

    var responseData = eval("(" + httpAjax.responseText + ")");

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
function Bouton6_afficherCarte(svgDocumentUrl) {

    let svg = document.getElementById('worldHigh');

    let s = chargerHttpXML(svgDocumentUrl);

    let serializer = new XMLSerializer();

    svg.innerHTML = serializer.serializeToString(s);

}

function Bouton7_makeCountriesClickable(){

    var countries = document.getElementById('worldHigh').children[0].getElementsByTagName('g')[0].children;

    for( let i = 0 ; i < countries.length ; i++ ){

        countries[i].addEventListener('click', function(){
            document.getElementById('countryNameDisplay').innerHTML = this.getAttribute('countryname');
        });
    }

}

function Bouton8_captureMouseMovement(){

    var countries = document.getElementById('worldHigh').children[0].getElementsByTagName('g')[0].children;

    for(let i = 0 ; i < countries.length ; i++){
        let previousColor = countries[i].style.fill;

        countries[i].addEventListener('mouseover' , function(){
            this.style.fill = '#404040';
        })

        countries[i].addEventListener('mouseleave',function (){
            this.style.fill = previousColor;
        })
    }

}

function Bouton9_addAutoComplete(){
    const inputField = document.getElementById("codePays");

    const button = document.getElementById("myButton9");

    const XMLDocument = chargerHttpXML('../countriesTP.xml');

    const parser = new DOMParser();

    const xpath = "//country/country_codes/cca2";

    const nodes = XMLDocument.evaluate(xpath, XMLDocument, null, XPathResult.ANY_TYPE, null);

    const options = [];

    // Adding the options from the XML file to the array
    let node = nodes.iterateNext();
    while (node) {
        options.push(node.textContent);
        node = nodes.iterateNext();
    }

    const datalist = document.createElement("datalist");
    datalist.id = "autoComplete";


    for( let option in options ){
        const optionElement = document.createElement("option");

        optionElement.setAttribute("value", options[option] );
        datalist.appendChild(optionElement);
    }

    inputField.appendChild(datalist);

    inputField.setAttribute("list" , datalist.id);

}



