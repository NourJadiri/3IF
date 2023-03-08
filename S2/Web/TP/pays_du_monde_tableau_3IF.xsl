<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:xs="http://www.w3.org/2001/XMLSchema"
                xmlns:array="http://www.w3.org/2005/xpath-functions/array"
                xmlns:map="http://www.w3.org/2005/xpath-functions/map"
                xmlns:math="http://www.w3.org/2005/xpath-functions/math"
                exclude-result-prefixes="#all"
                expand-text="yes"
                version="3.0">

    <xsl:output method="html"/>

    <xsl:template match="/">
        <html>
            <head>
                <title> Countries of the world </title>
            </head>

            <body style="background-color: white;">
                <h1>Information about the countries </h1>

                <!-- Ne pas oublier les // cuz metadonnes pas a la racine -->
                <xsl:apply-templates select="//metadonnees"/>

                
                <table border="3" width="600" align="center">
                    <tr>
                        <th> N° </th>
                        <th> Name </th>
                        <th> Capital </th>
                        <th> Coordinates </th>
                        <th> Neighbours </th>
                        <th> Flag </th>
                        <th> Spoken languages </th>
                    </tr>
                    

                    </table>
                <xsl:apply-templates select="countries"/>

            </body>
        </html>
    </xsl:template>

    <!-- Définiton de tous les templates utiles -->
    <xsl:template match="countries">
        <xsl:apply-templates select="country"/>
    </xsl:template>

    <!-- Section : metadonnees -->
    <xsl:template match="metadonnees">
        <p style="text-align: center; color: green;">
            Objectif : <xsl:value-of select="objectif"/>
        </p>
        <p>Mise en forme par Celia Djouadi, Nour Eljadiri (B3431)</p>
        <hr/><hr/>
        
    </xsl:template>

    <xsl:template match="country">
        <tr>
            
            <td>
                <xsl:value-of select="position()"/>
            </td>

            <xsl:apply-templates select="country_name"/>
            <xsl:apply-templates select="capital"/>
            <xsl:apply-templates select="coordinates"/>

            <td>
                <xsl:apply-templates select="borders/neighbour"/>
                <xsl:if test="not(borders) and landlocked = 'false'">
                    <xsl:text> Île </xsl:text>
                </xsl:if>
            </td>

            <!--TODO : refactor le code-->
            <td>
                <xsl:variable name="cca2_code">
                    <xsl:value-of select="translate(country_codes/cca2,'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz') "/>
                </xsl:variable>
                <img src = "http://www.geonames.org/flags/x/{$cca2_code}.gif" alt="" height="40" width = "60"/>
            </td>

            <!-- Utilisation de for-each sans template -->
            <td>
                <xsl:for-each select="languages/*">
                    <xsl:value-of select="."/>
                    <xsl:if test="position() != last()">
                        <xsl:text>, </xsl:text>
                    </xsl:if>
                </xsl:for-each>
            </td>


        </tr>
    </xsl:template>

    <xsl:template match="country_name">
        <td>
            <span style="color: green">
                <xsl:value-of select="offic_name"/>
                <xsl:text> </xsl:text>
            </span>
            <span style="color: black;">
                <xsl:value-of select="concat('(',common_name,')')"/>
            </span>
            <br/>
            <span style="color: blue;">
                <!-- Tester l'existance du nom en français -->
                <xsl:if test="native_name[@lang = 'fra']">
                    <xsl:text>Nom français : </xsl:text>
                    <xsl:value-of select="native_name[@lang = 'fra']"/>
                </xsl:if>
                </span>
        </td>
    </xsl:template>

    <xsl:template match="capital">
        <td>
            <xsl:value-of select="."/> 
        </td>
    </xsl:template> 

    <xsl:template match="coordinates">
        <td>
            <xsl:text>Latitude : </xsl:text>
            <xsl:value-of select="./@lat"/>
            <br/>
            <xsl:text>Longitude : </xsl:text>
            <xsl:value-of select="./@long"/>
        </td>
    </xsl:template>

    <xsl:template match="neighbour">
        <xsl:variable name="code">
            <xsl:value-of select="text()"/>
        </xsl:variable>
        
        <xsl:value-of select="//country/country_codes[cca3 = $code]/../country_name/common_name"/>
        <xsl:if test="position() != last()">
            <xsl:text>, </xsl:text>
        </xsl:if>
    </xsl:template>


</xsl:stylesheet>