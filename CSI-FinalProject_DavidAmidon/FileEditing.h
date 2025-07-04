/*
Author        : David Amidon
Class         : CSI - 240 : Advanced Programming
Assignment    : CSI-240 Final Project
*/

#pragma once
#include "Header.h"
#include "MediaClasses.h"

MediaBase* mediaType();
void addMedia(vector<MediaBase*>& vec);
void deleteMedia(vector<MediaBase*>& vec);
void editMedia(vector<MediaBase*>& vec);
void printAllMedia(vector<MediaBase*>& vec);
void searchMediaByCatagory(const vector<MediaBase*>& vec);
void searchMediaByName(const vector<MediaBase*>& vec);