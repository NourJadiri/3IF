<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html"/>

    <xsl:template match="/">
        <html>
            <head>
                <title>Countries of the world</title>
            </head>

            <body style="background-color: white;">
                <h1>Information about the countries</h1>

                <!-- Ne pas oublier les // cuz metadonnes pas a la racine -->
                <xsl:apply-templates select="//metadonnees"/>

                <xsl:call-template name="stats"/>

                <xsl:apply-templates select="//infosContinent/continent[not(.=preceding::continent)]"/>


            </body>
        </html>
    </xsl:template>

    <!-- Définiton de tous les templates utiles -->
    <!-- Section : metadonnees -->
    <xsl:template match="metadonnees">
        <p style="text-align: center; color: green;">
            Objectif :
            <xsl:value-of select="objectif"/>
        </p>
        <p>Mise en forme par Celia Djouadi, Nour Eljadiri (B3431)</p>
        <hr/>
        <hr/>

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
                    <xsl:text>Île</xsl:text>
                </xsl:if>
            </td>

            <!--TODO : refactor le code-->
            <td>
                <xsl:variable name="cca2_code">
                    <xsl:value-of
                            select="translate(country_codes/cca2,'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz') "/>
                </xsl:variable>
                <img src="http://www.geonames.org/flags/x/{$cca2_code}.gif" alt="" height="40" width="60"/>
            </td>

            <!-- Utilisation de for-each sans template -->
            <td>
                <xsl:for-each select="languages/*">
                    <xsl:value-of select="."/>
                    <xsl:if test="position() != last()">
                        <xsl:text>,</xsl:text>
                    </xsl:if>
                </xsl:for-each>
            </td>


        </tr>
    </xsl:template>

    <xsl:template match="continent">
        <!--titre de section-->
        <xsl:if test="current() != ''">
            <h3>
                Countries of continent
                <xsl:value-of select="current()"/>
                , by sub-regions:
            </h3>
        </xsl:if>

        <!--On itère sur toutes les subregions du fichier dont le continent associé est current()-->
        <xsl:for-each select="//infosContinent[continent = current()]/subregion">

            <!--appel du template de subregion si on n'a pas encore visité la subregion-->
            <xsl:apply-templates select="../subregion[not(. = preceding::subregion)]"/>
        </xsl:for-each>
    </xsl:template>

    <xsl:template match="subregion">
        <div style="margin: 20px;">
            <b>
                <xsl:value-of select="current()"/>
                ( <xsl:value-of select="count(//country[infosContinent/subregion=current()])"/> countries )
            </b>
        </div>

        <!--On crée une table pour chaque sous région-->
        <table border="3" width="100%" align="center">
        <tr style="text-align: center; font-weight: bold">
            <td>N°</td>
            <td>Name</td>
            <td>Capital</td>
            <td>Coordinates</td>
            <td>Neigbhours</td>
            <td>Flag</td>
            <td>Spoken languages</td>
        </tr>

            <!--on cherche dans tout le fichier tous les pays dont la subregion est celle qu'on traite actuellement-->
            <!--appel du template de country pour créer les entrées de données-->
            <xsl:apply-templates select="//country[infosContinent/subregion = current()]"/>
        </table>
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
                    <xsl:text>Nom français :</xsl:text>
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
            <xsl:text>Latitude :</xsl:text>
            <xsl:value-of select="./@lat"/>
            <br/>
            <xsl:text>Longitude :</xsl:text>
            <xsl:value-of select="./@long"/>
        </td>
    </xsl:template>

    <xsl:template match="neighbour">
        <xsl:variable name="code">
            <xsl:value-of select="text()"/>
        </xsl:variable>

        <xsl:value-of select="//country/country_codes[cca3 = $code]/../country_name/common_name"/>
        <xsl:if test="position() != last()">
            <xsl:text>,</xsl:text>
        </xsl:if>
    </xsl:template>

    <xsl:template name="stats">
        <xsl:call-template name="countries_with_more_than_two_lang"/>
        <xsl:call-template name="country_with_most_neighbour"/>

        <hr/>
    </xsl:template>

    <xsl:template name="countries_with_more_than_two_lang">
        <p>
            Countries where more than 2 languages are spoken :
        </p>
        <xsl:for-each select="//country[count(languages/*) > 2]/country_name/common_name">
            <li>
                <xsl:value-of select="current()"/>
                <xsl:text> : </xsl:text>
                <xsl:for-each select="../../languages/*">
                    <xsl:value-of select="concat(current(),' (',name(),')')"/>
                    <xsl:if test="position() != last()">
                        <xsl:text> , </xsl:text>
                    </xsl:if>
                </xsl:for-each>
            </li>
        </xsl:for-each>
    </xsl:template>

    <xsl:template name="country_with_most_neighbour">

        <xsl:variable name="max_neighbours">
            <xsl:for-each select="//country">
                <xsl:sort select="count(borders/neighbour)" data-type="number" order="descending"/>
                <xsl:if test="position() = 1">
                    <xsl:value-of select="count(borders/neighbour)"/>
                </xsl:if>
            </xsl:for-each>
        </xsl:variable>

        <div style="margin-top : 10px; margin-bottom: 10px">
            <xsl:text>Countries having the most neighbours : </xsl:text>

            <xsl:for-each select="//country">

                <xsl:if test="count(borders/neighbour) = $max_neighbours">
                    <xsl:value-of select="country_name/common_name"/>
                    <xsl:text> , </xsl:text>
                </xsl:if>
            </xsl:for-each>
            <xsl:text> nb voisins : </xsl:text>
            <xsl:value-of select="$max_neighbours"/>
        </div>

    </xsl:template>


</xsl:stylesheet>