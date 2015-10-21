#pragma once

#define GRID_MAX 8
#define GRID_MIN 0
#define OCT_OFFSET 72 //+1 OCTAVE
#define INTERVAL 4.0

#include "ofMain.h"
#include "slMetro.h"
#include "slRandom.h"
#include "slAdsr.h"
#include "Sound.hpp"

typedef enum direction_e {NEGATIVE, POSITIVE} direction_e;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        int move(int ag_A, int ag_B);
        void step();
        void positionCheck();
        bool positionCheck(int i);
        int createNote();
    
        slMetro *metro;
        slRandom random;
//        int grids[8];
        int ag1, ag2;
        int ag1_note, ag2_note;
        int ag1_note_active, ag2_note_active;
        int count;
    
        slAdsr adsr1, adsr1b;
        slAdsr adsr2, adsr2b;
        slAdsr *focused1, *focused2;
        adsr_t params;
        Sound sound;
        bool secondTrigger = false;
        bool trigger_at_same = false;
};
