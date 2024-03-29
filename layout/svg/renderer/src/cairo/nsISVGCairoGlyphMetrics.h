/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ----- BEGIN LICENSE BLOCK -----
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Mozilla SVG Cairo Renderer project.
 *
 * The Initial Developer of the Original Code is IBM Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Parts of this file contain code derived from the following files(s)
 * of the Mozilla SVG project (these parts are Copyright (C) by their
 * respective copyright-holders):
 *    layout/svg/renderer/src/gdiplus/nsSVGGDIPlusGlyphGeometry.cpp
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ----- END LICENSE BLOCK ----- */

#ifndef __NS_ISVGCAIRO_GLYPHMETRICS_H__
#define __NS_ISVGCAIRO_GLYPHMETRICS_H__

#include "nsISVGRendererGlyphMetrics.h"
#include <cairo.h>

// 193e2d48-3898-4bf3-b6bf-d7c00a8aba1f
#define NS_ISVGCAIROGLYPHMETRICS_IID \
{ 0x193e2d48, 0x3898, 0x4bf3, { 0xb6, 0xbf, 0xd7, 0xc0, 0x0a, 0x8a, 0xba, 0x1f } }


/**
 * \addtogroup gdiplus_renderer Cairo Rendering Engine
 * @{
 */

/**
 * 'Private' rendering engine interface
 */
class nsISVGCairoGlyphMetrics : public nsISVGRendererGlyphMetrics
{
public:
  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISVGCAIROGLYPHMETRICS_IID)

  NS_IMETHOD_(void) GetSubBoundingBox(PRUint32 charoffset, PRUint32 count, nsIDOMSVGRect * *aBoundingBox)=0;

  NS_IMETHOD_(cairo_font_t*) GetFont() = 0;
};

/** @} */

#endif // __NS_ISVGCAIRO_GLYPHMETRICS_H__
