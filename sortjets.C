/*
Simple macro showing how to access branches from the delphes output root file,
loop over events, and plot simple quantities such as the jet pt and the di-electron invariant
mass.

root -l examples/Example1.C'("delphes_output.root")'
*/

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif

//------------------------------------------------------------------------------

void sortjets(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");


  // Book histograms
  //TH1 *histJetPT1 = new TH1F("jet_pt1", "jet P_{T}", 100, 0.0, 1000.0);
  //TH1 *histJetPT2 = new TH1F("jet_pt2", "jet P_{T} second jet", 100, 0.0, 1000.0);
  //TH1 *histJetPT3 = new TH1F("jet_pt3", "jet P_{T} third jet", 100, 0.0, 1000.0);
  //TH1 *histJetPT4 = new TH1F("jet_pt4", "jet P_{T} fourth jet", 100, 0.0, 1000.0);
  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    // If event contains at least 1 jet
    if(branchJet->GetEntries() > 0)
    {
      for(int i=0; i < branchJet->GetEntries() ; i++)
      {
      // Take first jet
        Jet *jet = (Jet*) branchJet->At(i);

      //Second (third, fourth) jet
      // Jet *jet2 = (Jet*) branchJet->At(1);
      //Jet *jet3 = (Jet*) branchJet->At(2);
      //Jet *jet4 = (Jet*) branchJet->At(3);

      // Plot jet transverse momentum
      //histJetPT1->Fill(jet1->PT);
      //histJetPT2->Fill(jet2->PT);
      //histJetPT3->Fill(jet3->PT);
      //histJetPT4->Fill(jet4->PT);

      // Print jet transverse momentum
      //cout << "Jet1 pt: "<<jet1->PT << endl;
        cout << "Jet" << i << " pt: "<< jet->PT << endl;
      //cout << "Jet3 pt: "<<jet3->PT << endl;
      //cout << "Jet4 pt: "<< jet4->PT << endl;
      }
      cout << "number of jets: "<< branchJet->GetEntries() << endl;
    }

    for(int i=0; i < branchMissingET->GetEntries() ; i++){
      MissingET *met = (MissingET*) branchMissingET->At(i);
      cout << "Missing Energy: " << met->MET << endl;
    }
  }

  //TCanvas * c1 = new TCanvas("c1");
  //TCanvas * c2 = new TCanvas("c2");
  //TCanvas * c3 = new TCanvas("c3");
  //TCanvas * c4 = new TCanvas("c4");
  //c1->cd();
  // Show resulting histograms
  //histJetPT1->Draw();
  //histMass->Draw();
  //c2->cd();
  //histJetPT2->Draw();

  //c3->cd();
  //histJetPT3->Draw();

  //c4->cd();
  //histJetPT4->Draw();
}
