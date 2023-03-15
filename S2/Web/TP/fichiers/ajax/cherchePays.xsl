<?xml version="1.0" encoding="UTF-8" ?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:variable name="lowercase" select="'abcdefghijklmnopqrstuvwxyz'" />
    <xsl:variable name="uppercase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'" />
    <xsl:output method="html"/>

    <xsl:param name="code"/>
    <!--Transforming the code to uppercase for normalization-->
    <xsl:variable name="normalizedCode" select="translate($code, $lowercase, $uppercase)"/>


    <xsl:template match="/">
        <html>
            <body>
                <xsl:call-template name="cherchePays"/>
            </body>
        </html>

    </xsl:template>

    <xsl:template name="cherchePays">
        <pays>
            <span>
                <!--if the input field is not empty-->
                <xsl:if test="normalize-space($normalizedCode) != '' and //country[country_codes/* = $normalizedCode or callingCode = $normalizedCode]">
                    <!--normal functioning-->
                    <span>
                        <!--We display the country name-->
                        <p>Country :
                            <!--NOTE : Here we test not only for all the country codes but also for the calling code-->
                            <xsl:value-of select="//country[country_codes/* = $normalizedCode or callingCode = $normalizedCode]/country_name/offic_name"/>
                        </p>
                        <!--The capital-->
                        <p>
                            Capital :
                            <xsl:value-of select="//country[country_codes/* = $normalizedCode or callingCode = $normalizedCode]/capital"/>
                        </p>
                    </span>
                </xsl:if>

                <!--if the country code is not found-->
                <xsl:if test="not(//country[country_codes/* = $normalizedCode or callingCode = $normalizedCode])">
                    <span style="color: red;">
                        <xsl:text>
                            No country found with such a code...
                        </xsl:text>
                    </span>
                </xsl:if>

                <!--if the input field is empty-->
                <xsl:if test="normalize-space($normalizedCode) = ''">
                    <span style="color: red;">
                        <xsl:text>
                            Empty field, please try again...
                        </xsl:text>
                    </span>
                </xsl:if>
            </span>
        </pays>
    </xsl:template>
</xsl:stylesheet>

