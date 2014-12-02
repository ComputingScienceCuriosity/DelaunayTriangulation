#pragma once
// Si vous incluez SDKDDKVer.h, cela définit la dernière plateforme Windows disponible.

// Si vous souhaitez générer votre application pour une plateforme Windows précédente, incluez WinSDKVer.h et
// définissez la macro _WIN32_WINNT à la plateforme que vous souhaitez prendre en charge avant d'inclure SDKDDKVer.h.

#include <SDKDDKVer.h>
#include "delaunayopencv.h"


//Variables Globales//

//delaunay opencv 

//CvSubdiv2D* subdiv_finale;														  //Our outer bounding box

CvMemStorage* storage = cvCreateMemStorage(0)               ; 		              //Initialize the storage					  
CvPoint2D32f *dataDelaunay = new CvPoint2D32f [n_Points2D]  ;                       //Initialize 2D points type to get points in
CvPoint3D32f *data3d       = new CvPoint3D32f [n_Points2D]  ;
CvQuadEdge2D *edgeMain     = new CvQuadEdge2D [n_Points2D]  ;
//paint
    char win[] = "Triangulation Résultat , ImageDEV";
	char win2[] = "Triangulation Construction , ImageDEV";
	CvRect rect = { 0, 0, w , h };
	CvScalar active_facet_color = CV_RGB( 255, 0, 0 );
	CvScalar delaunay_color  = CV_RGB( 128,50,200);
	CvScalar bkgnd_color = CV_RGB(255,255,255);
	IplImage* img = cvCreateImage( cvSize(rect.width,rect.height), 8, 3 );
	IplImage* img2 = cvCreateImage( cvSize(rect.width,rect.height), 8, 3 );