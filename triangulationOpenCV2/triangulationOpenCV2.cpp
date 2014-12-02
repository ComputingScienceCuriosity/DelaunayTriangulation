// triangulationOpenCV2.cpp : définit le point d'entrée pour l'application console.
#include <cstdlib>
#include <windows.h>   // le standard Header de la plupart des programmes
#include <fstream>     // 
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#define fichierPoints2D "Point2D.txt"
#define fichier_STL_Triangulation3D "triangulation3D.stl"

using namespace std;

typedef struct _CvTriangle{
	CvPoint2D32f points2D[3];
} CvTriangle;

typedef struct _CvDelaunay_Triangles{
	CvTriangle*  _facets;
} CvDelaunay_Triangles;

CvDelaunay_Triangles Ens_Delaunay;
CvSubdiv2D* subdiv_finale;								//Our outer bounding box
CvRect rect = { 0, 0, 600, 600 }; 						//Storage for the Delaunay subdivsion
CvMemStorage* storage = cvCreateMemStorage(0); 			//Initialize the storage					  
CvPoint2D32f *dataDelaunay=NULL;                                 
		
 				  
//INITIALIZATION CONVENIENCE FUNCTION FOR DELAUNAY SUBDIVISION//
CvSubdiv2D* init_delaunay(CvMemStorage* storage,CvRect rect) {
	CvSubdiv2D* subdiv;                               
	subdiv = cvCreateSubdiv2D( CV_SEQ_KIND_SUBDIV2D ,sizeof(*subdiv), sizeof(CvSubdiv2DPoint) , sizeof(CvQuadEdge2D) , storage );
	cvInitSubdivDelaunay2D( subdiv, rect );  //rect sets the bounds
	return subdiv;
}
	
//chargement de la liste a de points a partire du fichier du points 2D

CvPoint2D32f* lecturePoints2D(int n){    

	CvPoint2D32f *data=NULL;
	data = new CvPoint2D32f[n] ;
     ifstream flux(fichierPoints2D);
      float xcor, ycor ;
	  if(!flux){ cerr<< "error" <<endl;
	  }else{        //a chaque espace il split le texte : 
		       cout << "Reading of the file :" << fichierPoints2D <<endl; 
			   int i=0;
			   cout << "Loading of 2D Points ..."<<endl; 
			   while((flux >> xcor) && (flux >> ycor) && (i <= n)){
			//	   cout << "///////////////////////////////////////////////////////////////" <<endl;
				   data[i].x = xcor;
                   data[i].y = ycor;      
			//	  cout << "2DPoints Coordinates  | x: |"<<  data[i].x << " | y: | " << data[i].y << endl;
				   i++;
               } 
			//   cout << "------------------------------------------------------------------------------" <<endl;
			//   cout <<endl<< "Reading of the file : -" << fichierPoints2D << "-done "<<endl;cout << endl << "File Closed :" <<endl;
			//   cout << "------------------------------------------------------------------------------" <<endl;
	  }flux.close();
      return data;
}


//Creation de l'insertion delaunay
CvSubdiv2D* create_delaunay_triangulation(CvSubdiv2D* subdiv,CvPoint2D32f *my_points){
	cout << endl << " Init of Delaunay Triangulation" << endl;
	CvPoint2D32f fp[152]; //point2D (x,y)
	my_points = NULL;
	my_points = lecturePoints2D(152);
	for(int i = 0; i < 152 ; i++ ) {
		//envoi des points
		fp[i] = my_points [i];
		//subdivision delaunay2D est insertion dans le tab de points 2D fp
		cvSubdivDelaunay2DInsert( subdiv , fp[i] );
		//cout << "Insertion of 2D points in Delaunay Subdiv ..."<< endl;
	}
	//cout <<endl << "Subdivision Iserted with succes" << endl;
	
	 return subdiv;
}
CvQuadEdge2D* get_delaunay_triangulation(CvSubdiv2D* subdiv){
	   
	Ens_Delaunay._facets =   new CvTriangle[subdiv->edges->active_count];
	CvSubdiv2DPoint* get_vtx_dalaunay[3];
	CvQuadEdge2D* outer_qedges[3];
	//triangle_delaunay = new CvSubdiv2DPoint[3] ;*/
	int k = 0;
	int I = 0;
	
	//cout << subdiv->edges->active_count << endl;
	/*for( I = 0; I < subdiv->edges->active_count  ; I++ ) {
		   for(int i = 0 ; i < 3 ; i++){
				get_vtx_dalaunay[i] = (CvSubdiv2DPoint*)cvGetSeqElem( (CvSeq*)subdiv, I);
				cout << " I:"<<I <<"i: " << i<<endl;
				I++;
		   }
	I--;
	}*/
	for( I = 0; I < subdiv->edges->active_count  ; I++ ) {
		for(int i = 0; i < 3; i++ ) {
		outer_qedges[i] =(CvQuadEdge2D*)cvGetSeqElem( (CvSeq*)(subdiv->edges), I );
//		cout <<"vertex : "<<i<<" x :"<< outer_qedges[i]->pt[0]->pt.x <<"y :"<<outer_qedges[i]->pt[0]->pt.y<<endl;
		
		I++;
		
		}
	I--;
	}
		cout <<"nombre vertexes"<<I<<endl;
		
	return *outer_qedges;
}
void fichier_txt_Points2D(){
	 FILE* stream = NULL ; 
     const char* namefile = fichier_STL_Triangulation3D;
     const char* name =     "triangulation3D";
     stream = fopen(namefile,"w");	
	 cout <<endl << "Begginig of STL storage : ....";
     if(stream != NULL)
     { 
        //debut d'ecriture
        fprintf(stream,"solid %s\n",name);  
		cout << " name" << endl;
        //********************** Transfert de la Triangluation ****************/      	 
	    for (int reconstruction = 0; reconstruction <  100 ; reconstruction ++){
             fprintf(stream," facet normal 0 0 0\n");
			  cout << endl << " name" << endl;
             fprintf(stream,"   outer loop\n");
			  cout << "   outer loop" << endl;
             for(int inc = 0 ; inc < 3 ; inc ++){
                /*point[inc].x = ensemble_tri.triangle3[reconstruction].points3[inc].x;
			    point[inc].y = ensemble_tri.triangle3[reconstruction].points3[inc].y;
			    point[inc].z = ensemble_tri.triangle3[reconstruction].points3[inc].z;
                point[inc].u = ensemble_tri.triangle3[reconstruction].points3[inc].u;
                point[inc].v = ensemble_tri.triangle3[reconstruction].points3[inc].v;*/
                fprintf(stream,"     vertex %f %f %f\n",50.0,50.0,50.0);
				cout <<"       vertex  1 2 3 " << endl; 
             }
		     fprintf(stream,"   endloop\n");
			 cout  << "   endloop" <<endl;
		     fprintf(stream," endfacet\n"); 
			  cout  << " endfacet" <<endl;
             //Fin de l'ecriture 
        }
        fprintf(stream,"endsolid %s\n",name);
		cout << "endsolid " << name << endl;
        cout << "__________________________________________________________________" <<endl;
		cout <<endl<<endl<< "			File writing is done "<< endl;

		cout <<endl<<endl<< "		This file: "<< name <<" is saved !"<< endl;
		cout <<endl<< "__________________________________________________________________" <<endl;
        fclose(stream);
     }else{cerr<< " Erreur lors de l'ecriture du fichier STL!" << endl;}  




}

//Création du fichier STL : 
void construction_Triangulation_ecriture_STL(){
     
     //passage de l'ensemle des points 3D 
	 CvPoint3D32f point[3];
	//************************ debut d'écriture STL *****************************
     FILE* stream = NULL ; 
     const char* namefile = fichier_STL_Triangulation3D;
     const char* name =     "triangulation3D";
     stream = fopen(namefile,"w");	
	 cout <<endl << "Begginig of STL storage : ....";
     if(stream != NULL)
     { 
        //debut d'ecriture
        fprintf(stream,"solid %s\n",name);  
		cout << " name" << endl;
        //********************** Transfert de la Triangluation ****************/      	 
	    for (int reconstruction = 0; reconstruction <  100 ; reconstruction ++){
             fprintf(stream," facet normal 0 0 0\n");
			  cout << endl << " name" << endl;
             fprintf(stream,"   outer loop\n");
			  cout << "   outer loop" << endl;
             for(int inc = 0 ; inc < 3 ; inc ++){
                /*point[inc].x = ensemble_tri.triangle3[reconstruction].points3[inc].x;
			    point[inc].y = ensemble_tri.triangle3[reconstruction].points3[inc].y;
			    point[inc].z = ensemble_tri.triangle3[reconstruction].points3[inc].z;
                point[inc].u = ensemble_tri.triangle3[reconstruction].points3[inc].u;
                point[inc].v = ensemble_tri.triangle3[reconstruction].points3[inc].v;*/
                fprintf(stream,"     vertex %f %f %f\n",50.0,50.0,50.0);
				cout <<"       vertex  1 2 3 " << endl; 
             }
		     fprintf(stream,"   endloop\n");
			 cout  << "   endloop" <<endl;
		     fprintf(stream," endfacet\n"); 
			  cout  << " endfacet" <<endl;
             //Fin de l'ecriture 
        }
        fprintf(stream,"endsolid %s\n",name);
		cout << "endsolid " << name << endl;
        cout << "__________________________________________________________________" <<endl;
		cout <<endl<<endl<< "			File writing is done "<< endl;

		cout <<endl<<endl<< "		This file: "<< name <<" is saved !"<< endl;
		cout <<endl<< "__________________________________________________________________" <<endl;
        fclose(stream);
     }else{cerr<< " Erreur lors de l'ecriture du fichier STL!" << endl;}  
}



int _tmain(int argc, _TCHAR* argv[])
{   
	dataDelaunay  = new CvPoint2D32f[152] ;							// To get 2D points in 
	dataDelaunay  = lecturePoints2D(152);				         	// Getting dataDelaunay points from the text file
	CvSubdiv2D* subdiv = init_delaunay( storage, rect);             // Creation of Delaunay subdivision
	subdiv = create_delaunay_triangulation( subdiv,dataDelaunay );	// Getting my finale_subdiv  
	cvCalcSubdivVoronoi2D ( subdiv );					            // Fill out Voronoi data in subdiv   
	get_delaunay_triangulation(subdiv);
				
	//construction_Triangulation_ecriture_STL();

	
	IplImage* img= cvLoadImage("box.png");
	cvNamedWindow("window");
	cvShowImage("window",img);
	cvClearSubdivVoronoi2D( subdiv );			// Clear the Voronoi from subdiv
	cvWaitKey();
	return 0;
}

