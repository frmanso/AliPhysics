#ifndef ALIFILTEREDEVENT_H
#include "AliFilteredEvent.h"
#endif
#include <AliFilteredTrack.h>
#include <TList.h>

ClassImp(AliFilteredEvent)

TClonesArray* AliFilteredEvent::fgTracks = 0;

AliFilteredEvent::AliFilteredEvent() :
  AliVEvent(),
  fCentrality(-1.0),
  fVertex(),
  fRunNr(0),
  fEventPlaneAngle(-10.0),
  fConnected(false),
  fNTracks(0),
  fTracks(0x0)
{
  //Constructor
  if(!fgTracks) fgTracks = new TClonesArray("AliFilteredTrack", 100000);
  fTracks = fgTracks;
  
}

AliFilteredEvent::AliFilteredEvent(const char* name) :
  AliVEvent(),
  fCentrality(-1.0),
  fVertex(),
  fRunNr(0),
  fEventPlaneAngle(-10.0),
  fConnected(false),
  fNTracks(0),
  fTracks(0x0)
{
  //Constructor
  if(!fgTracks) fgTracks = new TClonesArray("AliFilteredTrack", 100000);
  fTracks = fgTracks;
  
}
//____________________________________________________________________________
AliFilteredEvent::~AliFilteredEvent()
{
  //
  // De-Constructor
  //
  ClearEvent();
}


void AliFilteredEvent::ClearEvent() {
  fCentrality = -1.0;
  fVertex[0] = -20.0;
  fVertex[1] = -20.0;
  fVertex[2] = -20.0;
  fRunNr = 0;
  fEventPlaneAngle = -10.0;
  fNTracks = 0;
  if(fTracks) fTracks->Clear("C");
}

void AliFilteredEvent::ReadFromTree(TTree *tree, Option_t* opt){
     // Connects aod event to tree
  
  if(!tree){
    AliWarning("Zero Pointer to Tree \n");
    return;
  }
  // load the TTree
  if(!tree->GetTree())tree->LoadTree(0);
  
  // Try to find the Event
  AliFilteredEvent *event = 0;
  event = (AliFilteredEvent*)tree->GetTree()->GetUserInfo()->FindObject("Event");
  if(event){
    // This event is connected to the tree by definition, just say so
    event->SetConnected();
    fConnected = kTRUE;
    }// no aodEvent
  else {
      // we can't get the list from the user data, create standard content
      // and set it by hand
    AliFatal("Error, cannot find the event object in the tree.");
    }
  }
