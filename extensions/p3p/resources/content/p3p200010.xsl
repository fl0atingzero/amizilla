<?xml version="1.0"?>
<!-- ***** BEGIN LICENSE BLOCK *****
   - Version: MPL 1.1/GPL 2.0/LGPL 2.1
   -
   - The contents of this file are subject to the Mozilla Public License Version
   - 1.1 (the "License"); you may not use this file except in compliance with
   - the License. You may obtain a copy of the License at
   - http://www.mozilla.org/MPL/
   -
   - Software distributed under the License is distributed on an "AS IS" basis,
   - WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
   - for the specific language governing rights and limitations under the
   - License.
   -
   - The Original Code is the Platform for Privacy Preferences.
   -
   - The Initial Developer of the Original Code is
   - Netscape Communications Corporation.
   - Portions created by the Initial Developer are Copyright (C) 2002
   - the Initial Developer. All Rights Reserved.
   -
   - Contributor(s): Harish Dhurvasula <harishd@netscape.com>
   -                 Heikki Toivonen <heikki@netscape.com>
   -
   - Alternatively, the contents of this file may be used under the terms of
   - either the GNU General Public License Version 2 or later (the "GPL"), or
   - the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
   - in which case the provisions of the GPL or the LGPL are applicable instead
   - of those above. If you wish to allow use of your version of this file only
   - under the terms of either the GPL or the LGPL, and not to allow others to
   - use your version of this file under the terms of the MPL, indicate your
   - decision by deleting the provisions above and replace them with the notice
   - and other provisions required by the LGPL or the GPL. If you do not delete
   - the provisions above, a recipient may use your version of this file under
   - the terms of any one of the MPL, the GPL or the LGPL.
   -
   - ***** END LICENSE BLOCK ***** -->

<!DOCTYPE xsl:stylesheet SYSTEM "chrome://p3p/locale/p3p.dtd">
<!-- We try to support all the namespaces that are in
     use according to W3C: 
       http://www.w3.org/P3P/compliant_sites 
-->
<xsl:stylesheet 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
  xmlns:p3p="http://www.w3.org/2000/10/18/P3Pv1"
  version="1.0">

<!-- set the output properties -->
<xsl:output method="html"/>

<xsl:param name="policyUri"/>

<!-- POLICY -->
<xsl:template match="p3p:POLICY">
 <xsl:if test = "@discuri">
  &p3p.policy.discuri;
 </xsl:if>
 <xsl:if test = "@opturi">
  &p3p.policy.opturi;
 </xsl:if>
</xsl:template>

<!-- ENTITY -->

<xsl:template name="entity">
&p3p.entity;
</xsl:template>

<xsl:template match="p3p:ENTITY//p3p:DATA">
 <xsl:variable name="ref" select="@ref"/>
 <xsl:if test = "$ref='#business.name'">
   <xsl:value-of select="."/>&p3p.business.name.sep;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.postal.street'">
   <xsl:value-of select="."/>&p3p.business.street.sep;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.postal.city'">
   <xsl:value-of select="."/>&p3p.business.city.sep;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.postal.stateprov'">
   <xsl:value-of select="."/>&p3p.business.stateprov.sep;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.postal.postalcode'">
   <xsl:value-of select="."/>&p3p.business.postalcode.sep;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.postal.country'">
   <xsl:value-of select="."/>&p3p.business.country.sep;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.online.email'">
   <xsl:value-of select="."/>&p3p.business.email.sep;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.telecom.telephone.intcode'">
   <xsl:value-of select="."/>&p3p.business.telephone.intcode.sep;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.telecom.telephone.loccode'">
   &p3p.business.telephone.loccode.before;<xsl:value-of select="."/>&p3p.business.telephone.loccode.after;
 </xsl:if>
 <xsl:if test = "$ref='#business.contact-info.telecom.telephone.number'">
   <xsl:value-of select="."/>&p3p.business.telephone.number.sep;
 </xsl:if>
</xsl:template>

<xsl:template name="organization">
 <xsl:variable name="data" select="//p3p:DATA"/>
 <xsl:choose>
  <xsl:when test = "$data[@ref='#business.contact-info.online.uri']">
    &p3p.organization;
   <b>
    <xsl:element name="a">
     <xsl:attribute name="href">
      <xsl:value-of select="$data[@ref='#business.contact-info.online.uri']"/>
      </xsl:attribute>
       <xsl:attribute name="target">
        <xsl:text>_blank</xsl:text>
       </xsl:attribute>
      <xsl:value-of select="$data[@ref='#business.name']"/>
    </xsl:element>
   </b><br/>
  </xsl:when>
  <xsl:otherwise>
   <xsl:if test = "$data[@ref='#business.name']">
     &p3p.organization; <b><xsl:value-of select="$data[@ref='#business.name']"/></b>
   </xsl:if>
  </xsl:otherwise>
 </xsl:choose>
</xsl:template>


<!-- ACCESS -->

<xsl:template name="access">
&p3p.access;
</xsl:template>

<xsl:template match="p3p:ACCESS">
  <xsl:apply-templates mode="ACCESS" select="*"/>
</xsl:template>

<xsl:template mode="ACCESS" match="p3p:nonident"> 
  <li>&p3p.access.noident;</li>
</xsl:template>

<xsl:template mode="ACCESS" match="p3p:all"> 
  <li>&p3p.access.all;</li>
</xsl:template>

<xsl:template mode="ACCESS" match="p3p:contact-and-other"> 
  <li>&p3p.access.contactandother;
  </li>
</xsl:template>

<xsl:template mode="ACCESS" match="p3p:ident-contact"> 
  <li>&p3p.access.identcontact;</li>
</xsl:template>

<xsl:template mode="ACCESS" match="p3p:other-ident"> 
  <li>&p3p.access.otherident;</li>
</xsl:template>

<xsl:template mode="ACCESS" match="p3p:none"> 
  <li>&p3p.access.none;</li>
</xsl:template>

<!-- DISPUTE -->

<xsl:template name="dispute">
<a name="dispute"> &p3p.dispute; </a>
</xsl:template>

<xsl:template match="p3p:DISPUTES">
 <li>
 <xsl:variable name="res" select="@resolution-type"/>
 <xsl:if test = "$res='service'">
  &p3p.dispute.service;
  <xsl:if test = "@service">
   <xsl:apply-templates select="@short-description"/>
  </xsl:if>
 </xsl:if>
 <xsl:if test = "$res='independent'">
  &p3p.dispute.independent;
  <xsl:if test = "@service">
   <xsl:apply-templates select="@short-description"/>
  </xsl:if>
 </xsl:if>
 <xsl:if test = "$res='law'">
  &p3p.dispute.law;
  <xsl:if test = "@service">
   <xsl:apply-templates select="@short-description"/>
  </xsl:if>
 </xsl:if>
 <xsl:if test = "$res='court'">
   &p3p.dispute.court;
 </xsl:if>
 </li>
</xsl:template>

<xsl:template match="p3p:IMG">
 <xsl:if test = "position()=1">
   <p style="font-weight:bold">&p3p.privacyseal;</p>
   <a style="padding-left:1em;" href="{$policyUri}#dispute">&p3p.resolve;</a><br/><br/>
 </xsl:if>
  <xsl:choose>
   <xsl:when test = "@src">
     <img style="padding-left:1em;" src="{@src}" width="{@width}" height="{@height}"/>
   </xsl:when>
   <xsl:otherwise>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<xsl:apply-templates select="@alt"/>
   </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<!-- PURPOSE -->

<xsl:template name="purpose">
&p3p.purpose;
</xsl:template>

<xsl:template name="pseudo-analysis">
  <a class="anchor" message="&p3p.pseudoanalysis.init;">
  &p3p.clickhereforinfo;</a> 
</xsl:template>

<xsl:template name="pseudo-decision">
  <a class="anchor" message="&p3p.pseudodecision.init;">
  &p3p.clickhereforinfo;</a>
</xsl:template>

<xsl:template name="individual-analysis">
  <a class="anchor" message="&p3p.individualanalysis.init;">
  &p3p.clickhereforinfo;</a>
</xsl:template>

<xsl:template name="individual-decision">
  <a class="anchor" message="&p3p.individualdecision.init;">
  &p3p.clickhereforinfo;</a>
</xsl:template>

<xsl:template name="optin">
 <i>&p3p.optin.before;
 <xsl:choose>
  <xsl:when test = "//p3p:POLICY/@opturi">
   <xsl:element name="a">
    <xsl:attribute name="href">
      <xsl:apply-templates select="//p3p:POLICY/@opturi"/>
    </xsl:attribute>
    <xsl:attribute name="target">
       <xsl:text>_blank</xsl:text>
    </xsl:attribute>
    <xsl:text>&p3p.optin.1;</xsl:text>
   </xsl:element>
  </xsl:when>
  <xsl:otherwise>
   <xsl:text>&p3p.optin.2;</xsl:text>
  </xsl:otherwise>
 </xsl:choose>
  &p3p.optin.after;
 </i>
</xsl:template>

<xsl:template name="optout">
 <i>&p3p.optout.before;
 <xsl:choose>
  <xsl:when test = "//p3p:POLICY/@opturi">
   <xsl:element name="a">
    <xsl:attribute name="href">
      <xsl:apply-templates select="//p3p:POLICY/@opturi"/>
    </xsl:attribute>
    <xsl:attribute name="target">
     <xsl:text>_blank</xsl:text>
    </xsl:attribute>
    <xsl:text>&p3p.optout.1;</xsl:text>
   </xsl:element>
  </xsl:when>
  <xsl:otherwise>
   <xsl:text>&p3p.optout.2;</xsl:text>
  </xsl:otherwise>
 </xsl:choose>
  &p3p.optout.after;
 </i>
</xsl:template>

<xsl:template match="p3p:PURPOSE">
  <xsl:apply-templates mode="PURPOSE" select="*"/>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:current">
 <li>&p3p.purpose.current;</li>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:admin">
 <li>&p3p.purpose.admin;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:develop">
 <li>&p3p.purpose.develop;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:tailoring">
 <li>&p3p.purpose.tailoring;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:pseudo-analysis">
 <li>&p3p.purpose.pseudoanalysis;
     <xsl:call-template name="pseudo-analysis"/>
 </li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:pseudo-decision">
 <li>&p3p.purpose.pseudodecision;
    <xsl:call-template name="pseudo-decision"/>
 </li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:individual-analysis">
 <li>&p3p.purpose.individualanalysis;
     <xsl:call-template name="individual-analysis"/>
 </li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:individual-decision">
 <li>&p3p.purpose.individualdecision;
   <xsl:call-template name="individual-decision"/>
 </li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:contact">
 <li>&p3p.purpose.contact;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:historical">
 <li>&p3p.purpose.historical;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:telemarketing">
 <li>&p3p.purpose.telemarketing;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="PURPOSE" match="p3p:other-purpose">
 <xsl:choose>
  <xsl:when test="normalize-space(.)">
   <li><xsl:apply-templates select="."/></li>
  </xsl:when>
  <xsl:otherwise>
   <li style="color:red">&p3p.purpose.other;</li>
  </xsl:otherwise>
 </xsl:choose>
</xsl:template>

<!-- REMEDIES -->
<xsl:template match="p3p:REMEDIES">
 <xsl:apply-templates mode="REMEDIES" select="*"/>
</xsl:template>

<xsl:template mode="REMEDIES" match="p3p:correct">
 <li>&p3p.remedies.correct;</li>
</xsl:template>

<xsl:template mode="REMEDIES" match="p3p:money">
 <li>&p3p.remedies.money;</li>
</xsl:template>

<xsl:template mode="REMEDIES" match="p3p:law">
 <li>&p3p.remedies.law;</li>
</xsl:template>

<!-- RECIPIENT -->

<xsl:template name="recipent">
&p3p.recipient;
</xsl:template>

<xsl:template match="p3p:RECIPIENT">
 <xsl:apply-templates mode="RECIPIENT" select="*"/>
</xsl:template>

<xsl:template mode="RECIPIENT" match="p3p:ours">
 <li>&p3p.recipient.ours;</li>
</xsl:template>

<xsl:template mode="RECIPIENT" match="p3p:delivery">
 <li>&p3p.recipient.delivery;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="RECIPIENT" match="p3p:same">
 <li>&p3p.recipient.same;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="RECIPIENT" match="p3p:other-recipient">
 <li>&p3p.recipient.otherrecipient;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="RECIPIENT" match="p3p:unrelated">
 <li>&p3p.recipient.unrelated;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template mode="RECIPIENT" match="p3p:public">
 <li>&p3p.recipient.public;</li>
 <xsl:if test = ".[@required='opt-in']">
  <xsl:call-template name="optin"/>
 </xsl:if>
 <xsl:if test = ".[@required='opt-out']">
  <xsl:call-template name="optout"/>
 </xsl:if>
</xsl:template>

<xsl:template name="ours">
  <a class="anchor" message="&p3p.ours.init;">
  &p3p.clickhereforinfo;</a> 
</xsl:template>

<!-- RETENTION -->

<xsl:template name="retention">
&p3p.retention;
</xsl:template>

<xsl:template match="p3p:RETENTION">
 <xsl:apply-templates mode="RETENTION" select="*"/>
</xsl:template>

<xsl:template mode="RETENTION" match="p3p:no-retention">
 <li>&p3p.retention.no;<xsl:call-template name="noretention"/></li>
</xsl:template>

<xsl:template mode="RETENTION" match="p3p:stated-purpose">
 <li>&p3p.retention.statedpurpose;<xsl:call-template name="statedpurpose"/></li>
</xsl:template>

<xsl:template mode="RETENTION" match="p3p:legal-requirement">
 <li>&p3p.retention.legal;<xsl:call-template name="legalrequirement"/></li>
</xsl:template>

<xsl:template mode="RETENTION" match="p3p:business-practices">
 <li>&p3p.retention.businesspractices;</li>
</xsl:template>

<xsl:template mode="RETENTION" match="p3p:indefinitely">
 <li>&p3p.retention.indefinitely;</li>
</xsl:template>

<xsl:template name="noretention">
  <a class="anchor" message="&p3p.noretention.init;">
  &p3p.clickhereforinfo;</a> 
</xsl:template>

<xsl:template name="statedpurpose">
  <a class="anchor" message="&p3p.statedpurpose.init;">
  &p3p.clickhereforinfo;</a>
</xsl:template>

<xsl:template name="legalrequirement">
  <a class="anchor" message="&p3p.legalrequirement.init;">
  &p3p.clickhereforinfo;</a>
</xsl:template>

<xsl:template mode="RETENTION" match="p3p:indefinitely">
 <li>&p3p.retention.indefinitely;</li>
</xsl:template>

<!-- CATEGORIES -->

<xsl:template name="categories">
&p3p.categories;
</xsl:template>

<xsl:template match="p3p:CATEGORIES">
 <xsl:apply-templates mode="CATEGORIES" select="*"/>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:physical">
 <li>&p3p.categories.physical;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:online">
 <li>&p3p.categories.online;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:uniqueid">
 <li>&p3p.categories.uniqueid;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:purchase">
 <li>&p3p.categories.purchase;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:financial">
 <li>&p3p.categories.financial;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:computer">
 <li>&p3p.categories.computer;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:navigation">
 <li>&p3p.categories.navigation;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:interactive">
 <li>&p3p.categories.interactive;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:demographic">
 <li>&p3p.categories.demographic;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:content">
 <li>&p3p.categories.content;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:state">
 <li>&p3p.categories.state;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:political">
 <li>&p3p.categories.political;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:health">
 <li>&p3p.categories.health;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:preference">
 <li>&p3p.categories.preference;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:location">
 <li>&p3p.categories.location;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:government">
 <li>&p3p.categories.government;</li>
</xsl:template>

<xsl:template mode="CATEGORIES" match="p3p:other-category">
 <xsl:choose>
  <xsl:when test="normalize-space(.)">
   <li><xsl:apply-templates select="."/></li>
  </xsl:when>
  <xsl:otherwise>
   <li>&p3p.categories.other;</li>
  </xsl:otherwise>
 </xsl:choose>
</xsl:template>

<!-- CONSEQUENCE -->

<xsl:template name="consequence">
&p3p.consequence;
</xsl:template>

<xsl:template match="p3p:CONSEQUENCE">
 <li><xsl:apply-templates select="./node()"/></li>
</xsl:template>

<!-- NON-IDENTIFIABLE -->

<xsl:template name="non-identifiable">
<u>&p3p.nonidentifiable;</u><br/>
</xsl:template>

<!-- STATEMET -->

<xsl:template match="p3p:STATEMENT">
 <xsl:if test = "position()=1">
  &p3p.statement;
  <ul>
  <xsl:for-each select="//p3p:POLICY/p3p:STATEMENT">
   <xsl:variable name="ctr" select="position()"/>
   <li><a href="{$policyUri}#statement{$ctr}">&p3p.statement.1;<xsl:value-of select="$ctr"/></a></li>
 </xsl:for-each>
 </ul>
 </xsl:if>
 <xsl:variable name="ctr" select="position()"/>
 <p style="font-weight:bold">
  <a name="statement{$ctr}">&p3p.statement.2;<xsl:value-of select="$ctr"/></a>
 </p>
 
 <xsl:if test = "./p3p:NON-IDENTIFIABLE[position()=1]">
   <xsl:call-template name="non-identifiable"/>
 </xsl:if>

 <xsl:if test = "./p3p:DATA-GROUP/p3p:DATA/p3p:CATEGORIES[position()=1]">
   <xsl:call-template name="categories"/>
 </xsl:if>
 <ul><xsl:apply-templates select="./p3p:DATA-GROUP/p3p:DATA/p3p:CATEGORIES"/></ul>
 
 <xsl:if test = "./p3p:PURPOSE[position()=1]">
   <xsl:call-template name="purpose"/>
 </xsl:if>
 <ul><xsl:apply-templates select="./p3p:PURPOSE"/></ul>
 
 <xsl:if test = "./p3p:RECIPIENT[position()=1]">
   <xsl:call-template name="recipent"/>
 </xsl:if>
 <ul><xsl:apply-templates select="./p3p:RECIPIENT"/></ul>
 
 <xsl:if test = "./p3p:RETENTION[position()=1]">
   <xsl:call-template name="retention"/>
 </xsl:if>
 <ul><xsl:apply-templates select="./p3p:RETENTION"/></ul>

 <xsl:if test = "./p3p:CONSEQUENCE[position()=1]">
   <xsl:call-template name="consequence"/>
 </xsl:if>
 <ul><xsl:apply-templates select="./p3p:CONSEQUENCE"/></ul>
</xsl:template>

<!-- ROOT RULE -->
<xsl:template match="/">
<html>
 <head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
  <title id="topic">&p3p.html.title;</title>
  <style>
    html { 
      font-family: sans-serif;
      padding: 0.5em; 
      background: #ffffff; 
      color: #000000;
    }
    a[class=anchor] {
      color: blue; 
      cursor: pointer;
      text-decoration: underline;
    }
    a:active {
      color: red; 
    }
  </style>
 </head>
 <body>
   <xsl:call-template name="organization"/>
   <p style="font-weight:bold"><a name="summary">&p3p.html.td.1;</a></p>
   <xsl:apply-templates select=".//p3p:POLICY"/>
   <xsl:apply-templates select=".//p3p:POLICY/p3p:DISPUTES-GROUP/p3p:DISPUTES/p3p:IMG"/>
   <p style="font-weight:bold"><a name="statement">&p3p.html.td.2;</a></p>
   <xsl:apply-templates select=".//p3p:POLICY/p3p:STATEMENT"/>
   <p style="font-weight:bold"><a name="access">&p3p.html.td.3;</a></p>
   <xsl:if test = ".//p3p:POLICY/p3p:ACCESS[position()=1]">
     <xsl:call-template name="access"/>
   </xsl:if>
   <ul>
    <xsl:apply-templates select=".//p3p:POLICY/p3p:ACCESS"/>
   </ul>
   <xsl:if test = ".//p3p:POLICY/p3p:DISPUTES-GROUP/p3p:DISPUTES[position()=1]">
    <xsl:call-template name="dispute"/>
   </xsl:if>
   <ul>
    <xsl:apply-templates select=".//p3p:POLICY/p3p:DISPUTES-GROUP/p3p:DISPUTES"/>
   </ul>
   <xsl:if test = ".//p3p:POLICY/p3p:ENTITY/p3p:DATA-GROUP/p3p:DATA[position()=1]">
     <xsl:call-template name="entity"/>
   </xsl:if>
   <ul>
     <xsl:apply-templates select=".//p3p:POLICY/p3p:ENTITY/p3p:DATA-GROUP/p3p:DATA">
     <xsl:sort select=".[@ref='#business.contact-info.telecom.telephone.number']"/>
     <xsl:sort select=".[@ref='#business.contact-info.telecom.telephone.loccode']"/>
     <xsl:sort select=".[@ref='#business.contact-info.telecom.telephone.intcode']"/>
     <xsl:sort select=".[@ref='#business.contact-info.online.email']"/>
     <xsl:sort select=".[@ref='#business.contact-info.postal.country']"/>
     <xsl:sort select=".[@ref='#business.contact-info.postal.postalcode']"/>
     <xsl:sort select=".[@ref='#business.contact-info.postal.stateprov']"/>
     <xsl:sort select=".[@ref='#business.contact-info.postal.city']"/>
     <xsl:sort select=".[@ref='#business.contact-info.postal.street']"/>
     <xsl:sort select=".[@ref='#business.name']"/>
     </xsl:apply-templates>
   </ul>
 </body>
</html>
</xsl:template>
</xsl:stylesheet>





