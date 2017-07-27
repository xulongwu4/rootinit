{
    gROOT->Macro("HallA_style.cxx");

    //gStyle->SetTitleX(0.5);
    //gStyle->SetTitleAlign(23);
    //gStyle->SetTitleBorderSize(0);
    //gStyle->SetTitleFillColor(0);

    gStyle->SetPadTopMargin(0.10);
    gStyle->SetPadLeftMargin(0.125);
    gStyle->SetPadBottomMargin(0.10);

    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);

    gStyle->SetLabelSize(0.04, "XYZ");

    gStyle->SetTitleFont(132, "XYZ");
    gStyle->SetTitleSize(0.05, "XYZ");

    //gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
    //gStyle->SetOptDate(0);

    //gStyle->SetFrameBorderMode(0);
    //gStyle->SetCanvasBorderMode(0);
    //gStyle->SetPadBorderMode(0);
    //gStyle->SetCanvasColor(0);
    //gStyle->SetPadColor(0);

    //gStyle->SetFuncColor(kRed);
}
