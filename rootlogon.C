{
    TStyle* myStyle = new TStyle("myStyle","My Root Styles");

    myStyle->SetPalette(1);
    myStyle->SetTitleX(0.5);
    myStyle->SetTitleAlign(23);
    myStyle->SetTitleBorderSize(0);
    myStyle->SetTitleFillColor(0);

    myStyle->SetPadBottomMargin(0.12);
    myStyle->SetPadTopMargin(0.08);
    myStyle->SetPadLeftMargin(0.12);
    //myStyle->SetPadRightMargin(0.1);
    myStyle->SetPadRightMargin(0.06);

    myStyle->SetPadTickX(1);
    myStyle->SetPadTickY(1);
    myStyle->SetPadGridX(0);
    myStyle->SetPadGridY(0);

    myStyle->SetOptStat(0);
    myStyle->SetOptTitle(0);
    myStyle->SetOptDate(0);

    myStyle->SetFrameBorderMode(0);
    myStyle->SetCanvasBorderMode(0);
    myStyle->SetPadBorderMode(0);
    myStyle->SetCanvasColor(0);
    myStyle->SetPadColor(0);

    myStyle->SetFuncColor(kRed);

    myStyle->SetTitleFont(132,"xyz");
    myStyle->SetTitleSize(0.05,"xyz");
    myStyle->SetLabelSize(0.04,"xyz");
    //myStyle->SetTitleOffset(1.2,"y");
}
