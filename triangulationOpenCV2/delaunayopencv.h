// stdafx.h : fichier Include pour les fichiers Include système standard,
//**************************************Includes**************************************************/
#pragma once

#ifndef SKIP_INCLUDES

#include <cstdlib>
#include <windows.h>   
#include <fstream>     
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#endif
//**************************************Defines**************************************************/
#if defined WIN32 || defined _WIN32
#define h 600 
#define w  600
#define fichierPoints2D "Point2D.txt"
#define fichierPoints3D "Point3D.txt" 
#define file_delaunay2D "Delaunay2D.stl"  
#define fichier_STL_Triangulation3D "triangulation3D.stl"
#define fichier_voronoi "voronoi.txt"
#define delaunay2dpoints "delaunay2D.txt"
#define delaunay2Dpoints_windowed "delaunay_windowed.txt"
#define reconstruction3D "reconstruction3D.stl"
#define n_Points2D 363

#endif
using namespace std;
/*-----------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------*/
 				  //***********************Fonctions **********************************// 
/*--------------------------------------------------------------------------------------------------*/
void help();
CvRect init_Cv_Storage( int x , int y , int width , int height);
CvSubdiv2D* init_delaunay(CvMemStorage* storage,CvRect rect);
CvPoint2D32f* lecturePoints2D(int n);
CvPoint3D32f* lecturePoints3D(int n);
CvSubdiv2D* create_delaunay_subdivision(CvSubdiv2D* subdiv,CvPoint2D32f *my_points,int t);
void tri_triangles();
void construction_Triangulation_ecriture_STL(CvSubdiv2D* subdiv);
void construction_Triangulation_Delaunay2D_STL();
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************Fonctions of paint***********************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_subdiv_point( IplImage* img, CvPoint2D32f fp, CvScalar color );
void draw_subdiv_edge( IplImage* img, CvSubdiv2DEdge edge, CvScalar color );
void draw_subdiv( IplImage* img, CvSubdiv2D* subdiv, CvScalar delaunay_color );
void draw_subdiv_facet( IplImage* img, CvSubdiv2DEdge edge );
void paint_voronoi( CvSubdiv2D* subdiv, IplImage* img );
void optimisation_delaunay_triangles();
void Mypaint(CvSubdiv2D* subdiv,CvPoint2D32f *points2D,IplImage* img2,
	CvScalar bkgnd_color,char window_name2[],CvScalar delaunay_color,CvScalar active_facet_color,int i);
void run();
/**************************************End of Header***********************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////