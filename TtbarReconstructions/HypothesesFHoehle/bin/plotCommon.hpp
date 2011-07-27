/**
 * @file
 *
 * @author      Martina Davids [Martina.Davids@Physik.RWTH-Aachen.DE]
 * @author      Markus Duda [Markus.Duda@Physik.RWTH-Aachen.DE]
 * @author      Felix Höhle [hoehle@Physik.RWTH-Aachen.DE]
 *
 * @version     $Revision$
 *
 * @brief
 * Common plot macro functions.
 *
 */

#include "TROOT.h"
#include "TStyle.h"
//======================================================================
/**
 * setup ROOT's gStyle
 */
void
InitgStyle()
{
// {{{
    // reset everything
    //gROOT->Reset();

    // canvas
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetCanvasDefH(600);
    gStyle->SetCanvasDefW(800);
    gStyle->SetCanvasDefX(0);
    gStyle->SetCanvasDefY(0);

    // pad
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadColor(0);

    // frame
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetFrameFillStyle(0);
    gStyle->SetFrameLineColor(1);
    gStyle->SetFrameLineStyle(1);
    gStyle->SetFrameLineWidth(1);

    // fit and fit-function
    gStyle->SetOptFit(1111);
    gStyle->SetFitFormat("5.4g");

    // statistics box
    gStyle->SetOptStat("nemr");//1001100
    gStyle->SetStatColor(0);
    gStyle->SetStatFont(42);
    gStyle->SetStatFontSize(0.025);
    gStyle->SetStatTextColor(1);
    gStyle->SetStatFormat("6.4g");
    gStyle->SetStatBorderSize(1);
    gStyle->SetStatX(0.95);
    gStyle->SetStatY(0.95);
    gStyle->SetStatW(0.15);
    gStyle->SetStatH(0.15);

    // margins
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadBottomMargin(0.1);
    gStyle->SetPadLeftMargin(0.1);
    gStyle->SetPadRightMargin(0.04);

    // global title
    gStyle->SetOptTitle(0);

    // axis titles
    gStyle->SetTitleColor(1, "XYZ");
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetTitleSize(0.06, "XYZ");
    gStyle->SetTitleXOffset(0.65);
    gStyle->SetTitleYOffset(0.8);

    // axis labels
    gStyle->SetLabelColor(1, "XYZ");
    gStyle->SetLabelFont(42, "XYZ");
    gStyle->SetLabelOffset(0.007, "XYZ");
    //gStyle->SetLabelSize(0.05, "XYZ");
    gStyle->SetLabelSize(0.03, "XYZ");

    // axis
    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kFALSE);
    gStyle->SetTickLength(0.03, "XYZ");
    gStyle->SetNdivisions(10510, "XYZ");//510 50510 (20510, "XYZ");
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
/*
    // markers and error markers
    gStyle->SetErrorX(0);
    gStyle->SetEndErrorSize(2);
    gStyle->SetErrorMarker(20);
    gStyle->SetMarkerStyle(20);
*/
    // force this style on loaded objects, esp. histograms
    gROOT->ForceStyle();

}

