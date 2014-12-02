// stdafx.cpp : fichier source incluant simplement les fichiers Include standard
// triangulationOpenCV2.pch représente l'en-tête précompilé
// stdafx.obj contient les informations de type précompilées

#include "delaunayopencv.h"

#include "targetver.h"
int** x;

int nombre_triangles = 0 ; 
typedef struct Triangle{
	CvPoint2D32f a;
	CvPoint2D32f b;
	CvPoint2D32f c;
}TRIANGLE;

TRIANGLE* triangle;

typedef struct Point5{
	float x,y,z;
	float u,v;
}POINT5;

POINT5 *data5 = new POINT5[n_Points2D];
CvPoint2D32f* dataTriangle=NULL;




 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
 //*******************************************Debut des Fonctions****************************************************
 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
 void help()
{
	printf("\nThis program is used for 3D Triangulation Reconstruction\n"
			"You can also generate a Delaunay Triangulation with\n\n");
}
 //partie processing

 //Storage for the Delaunay subdivsion
CvRect init_Cv_Storage( int x , int y , int width , int height){
	CvRect rect = { x, y, width, height }; 						
	return rect;
	}

//INITIALIZATION CONVENIENCE FUNCTION FOR DELAUNAY SUBDIVISION//
CvSubdiv2D* init_delaunay(CvMemStorage* storage,CvRect rect) {
	CvSubdiv2D* subdiv;                               
	subdiv = cvCreateSubdiv2D( CV_SEQ_KIND_SUBDIV2D ,sizeof(*subdiv), sizeof(CvSubdiv2DPoint) , sizeof(CvQuadEdge2D) , storage );
	cvInitSubdivDelaunay2D( subdiv, rect );  //rect sets the bounds
	return subdiv;
}
	
//chargement de la liste a de points a partire du fichier du points 2D

CvPoint2D32f* lecturePoints2D(int n){    
	 
	 cout << "Reading of the file :" << fichierPoints2D <<endl; 
	 cout << "Loading of 2D Points ..."<<endl; 
	
	 CvPoint2D32f *data=NULL;
	 data = new CvPoint2D32f[n] ;
     ifstream flux(fichierPoints2D);
      float xcor, ycor ;
	  if(!flux){ cerr<< "error" <<endl;
	  }else{        //a chaque espace il split le texte : 
		     
			   int i=0;
			  
			   while((flux >> xcor) && (flux >> ycor) && (i <= n)){
				   data[i].x = xcor;
                   data[i].y = ycor;
				   data5[i].u = xcor;
				   data5[i].v = ycor;
				   i++;
               } 
			   cout << "------------------------------------------------------------------------------" <<endl;
			   cout <<endl<< "Reading done "<<endl;cout << endl << "File Closed :" <<endl;
			   cout << "------------------------------------------------------------------------------" <<endl;
	  }flux.close();
      return data;
}

CvPoint3D32f* lecturePoints3D(int n){
	  cout << "------------------------------------------------------------------------------" <<endl;
	  cout << "Reading of file :" << fichierPoints3D <<endl; 
	  cout << "Loading of 3D Points ..."<<endl; 
	 CvPoint3D32f *data3=NULL;
	 data3 = new CvPoint3D32f[n] ;
     ifstream flux(fichierPoints3D);
      float xcor, ycor , zcor;
	  if(!flux){ cerr<< "error" <<endl;
	  }else{        //a chaque espace il split le texte : 
		       
			   int i=0;
			
			   while((flux >> xcor) && (flux >> ycor) &&(flux >> zcor)&&(i <= n)){
				   
				   data3[i].x = xcor; data5[i].x = xcor;
                   data3[i].y = ycor; data5[i].y = ycor;
				   data3[i].z = zcor; data5[i].z = zcor;
				  
				 
				   i++;
               } 
			   cout << "------------------------------------------------------------------------------" <<endl;
			   cout <<endl<< "Reading done "<<endl;cout << endl << "File Closed :" <<endl;
			   cout << "------------------------------------------------------------------------------" <<endl;
	  }flux.close();
      return data3;
}



//Creation de l'insertion delaunay
CvSubdiv2D* create_delaunay_subdivision(CvSubdiv2D* subdiv,CvPoint2D32f *my_points,int t){
	cout << "Insertion of 2D points in Delaunay Subdiv ..."<< endl;
	cout << endl << " Init of Delaunay Triangulation" << endl;
	CvPoint2D32f fp[n_Points2D]; //point2D (x,y)
	my_points = NULL;
	my_points = lecturePoints2D(t);
	for(int i = 0; i < t ; i++ ) {
		//envoi des points
		fp[i] = my_points [i];
		//subdivision delaunay2D est insertion dans le tab de points 2D fp Création incrémentale de la triangulation
		cvSubdivDelaunay2DInsert( subdiv , fp[i] );	
		//Affichage de la création et ajout de points		
	}
	cout <<endl << "Subdivision Iserted with succes" << endl;
	
	 return subdiv;
}

void tri_triangles(){
	//Randing Triangles ... 
	int size = nombre_triangles * 3 ;
	dataTriangle = new CvPoint2D32f[size] ;
	int i = 0; 
	int j = 0;
    int k = 0;
	CvPoint2D32f* tmp = new CvPoint2D32f[1];
	for(i = 0 ; i < size  ; i +=3 ){

			dataTriangle[i]   = triangle[k].a;
            dataTriangle[i+1] = triangle[k].b;
			dataTriangle[i+2] = triangle[k].c;
			
			k++;
			
		}

/*	for(j=0 ; j < size ; j+=3){
		
		for(int l=0;l<2;l++){
		
			if(dataTriangle[j].x < dataTriangle[j+1].x){
				
				tmp[0] = dataTriangle[j];
				dataTriangle[j]= dataTriangle[j+1];
				dataTriangle[j+1]= tmp[0];
            }
			j++;

		}
	}
	*/

/*	for(i=0 ; i < size ; i++){
		
	   cout<<"data x:" << dataTriangle[i].x << "data y:" << dataTriangle[i].y<< endl;
		
	}*/

}

//Creating Of the STL FILE AND MATCHING 
void construction_Triangulation_ecriture_STL(CvSubdiv2D* subdiv){
    
	 cout <<endl << "Generating of STL file : PLEASE WAIT ..." << endl ;
     FILE* stream = NULL ; 
     const char* namefile = fichier_STL_Triangulation3D;
     const char* name     = "triangulation3D";
     stream = fopen(namefile,"w");	
	 
     if(stream != NULL)
     { 
       fprintf(stream,"solid %s\n",name);  
	   bool match = false ;
       int I = 0;
	   int i = 0; 
	   int j = 0 ;
	   int mat = 0 ;
	 				
	   for( I = 0; I < nombre_triangles*3 -2 ; I++ ) {
			 		
					fprintf(stream," facet normal 0 0 0\n");
					fprintf(stream,"    outer loop\n");
					
					for( mat = 0; mat < 3; mat++ ) {
							match = false;
						for(int j = 0 ; j < n_Points2D  ; j++){
						
							if(( dataTriangle[I+mat].x == data5[j].u  )&&( dataTriangle[I+mat].y == data5[j].v  )&&( match==false )){
						    	
								fprintf(stream,"		  vertex %f %f %f\n",data5[j].x,data5[j].y,data5[j].z);
								
								match = true ;

							}
								
						}
						
					}
					
					fprintf(stream,"    endloop\n");
					fprintf(stream," endfacet\n");
				
				 
        }    
       
				 
         
        fprintf(stream,"endsolid %s\n",name);
       cout << "__________________________________________________________________" <<endl;
		cout <<endl<<endl<< "			    File writing is done "<< endl;
		cout <<endl << "	                 3D Reconstruction finished" << endl;  
		cout <<endl<<endl<< "		The file: - "<< name <<" - is saved with succes !"<< endl;
		cout <<endl<< "__________________________________________________________________" <<endl;
        fclose(stream);
     }else{cerr<< " Error while writing in The STL FILE!" << endl;}  
	
}

//Creating of Delaunay TRIANGLES :

void construction_Triangulation_Delaunay2D_STL(){
    
	 cout << endl << "Generating of STL Delaunay2D file : PLEASE WAIT ... " << endl ;
     FILE* stream = NULL ; 
     const char* namefile = file_delaunay2D;
     const char* name     = "Delaunay2D";
     stream = fopen(namefile,"w");	
	 
     if(stream != NULL)
     { 
       fprintf(stream,"solid %s\n",name);  
	 
       int I = 0;
	   int i = 0; 
	   int j = 0 ;
	   			
					for(i=0 ; i < nombre_triangles*3; i+=3){
					
					fprintf(stream," facet normal 0 0 0\n");
					fprintf(stream,"    outer loop\n");
	
				       for(j = 0 ; j<3 ; j++){
						    	
						fprintf(stream,"		  vertex %f %f %f\n",dataTriangle[i+j].x,dataTriangle[i+j].y,0);
					   
						}
					fprintf(stream,"    endloop\n");
					fprintf(stream," endfacet\n");

					}	
						 
         
       
				 
         
        fprintf(stream,"endsolid %s\n",name);
        cout << "__________________________________________________________________" <<endl;
		cout <<endl<<endl<< "			    File writing is done "<< endl;
		cout <<endl << "	                Delaunay Generating Finished" << endl;  
		cout <<endl<<endl<< "		The file: - "<< name <<" - is saved with succes !"<< endl;
		cout <<endl<< "__________________________________________________________________" <<endl;
        fclose(stream);
     }else{cerr<< " Error while writing in The STL Delaunay2D FILE!" << endl;}  
	 
}



//Painting Part
//Create the point proprieties and shaping
void draw_subdiv_point( IplImage* img, CvPoint2D32f fp, CvScalar color )
{
    cvCircle( img, cvPoint(cvRound(fp.x), cvRound(fp.y)), 3, color, CV_FILLED, 8, 0 );
}
//Drawaing the edges of the courant subdiv point : 
void draw_subdiv_edge( IplImage* img, CvSubdiv2DEdge edge, CvScalar color )
{
	
    CvSubdiv2DPoint* org_pt;
    CvSubdiv2DPoint* dst_pt;
    CvPoint2D32f org;
    CvPoint2D32f dst;
    CvPoint iorg, idst;
	
    org_pt = cvSubdiv2DEdgeOrg(edge);
    dst_pt = cvSubdiv2DEdgeDst(edge);

    if( org_pt && dst_pt )
    {
        org = org_pt->pt;
        dst = dst_pt->pt;
		 
        iorg = cvPoint( cvRound( org.x ), cvRound( org.y ));
	    idst = cvPoint( cvRound( dst.x ), cvRound( dst.y ));

        cvLine( img, iorg, idst, color, 1, CV_AA, 0 );
		
    }
}
//Drawing subdivision
void draw_subdiv( IplImage* img, CvSubdiv2D* subdiv,
                  CvScalar delaunay_color )
{
	
    CvSeqReader  reader;
    int i, total = subdiv->edges->total;
    int elem_size = subdiv->edges->elem_size;

    cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );
	int k = 0 ;
    for( i = 0; i < total; i++ )
    {
		
        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);
		
        if( CV_IS_SET_ELEM( edge ))
        {
          
            draw_subdiv_edge( img, (CvSubdiv2DEdge)edge, delaunay_color );
	
        }
		
        CV_NEXT_SEQ_ELEM( elem_size, reader );
		
    }

}

//Location of the point while creating the hullvex
void locate_point( CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img,
                   CvScalar active_color )
{
    CvSubdiv2DEdge e;
    CvSubdiv2DEdge e0 = 0;
    CvSubdiv2DPoint* p = 0;

    cvSubdiv2DLocate( subdiv, fp, &e0, &p );

    if( e0 )
    {
        e  = e0;
        do
        {
            draw_subdiv_edge( img, e, active_color );
			//e
            e  = cvSubdiv2DGetEdge(e,CV_NEXT_AROUND_LEFT);
		
        }
        while( e != e0 );
    }

    draw_subdiv_point( img, fp, active_color );
}

//drawing of the facet 
void draw_subdiv_facet( IplImage* img, CvSubdiv2DEdge edge )
{
    CvSubdiv2DEdge t = edge;
    int i, count = 0;
    CvPoint* buf = 0;

    // count number of edges in facet
    do
    {
        count++;
        t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );
		
    } while (t != edge );

    buf = (CvPoint*)malloc( count * sizeof(buf[0]));

    // gather points
    t = edge;
    for( i = 0; i < count; i++ )
    {
        CvSubdiv2DPoint* pt = cvSubdiv2DEdgeOrg( t );
		
        if( !pt ) break;
		

        buf[i] = cvPoint( cvRound(pt->pt.x), cvRound(pt->pt.y));
		
        t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );	
    } 
	

    if( i == count )
    {
        CvSubdiv2DPoint* pt = cvSubdiv2DEdgeDst( cvSubdiv2DRotateEdge( edge, 1 ));

        //cvFillConvexPoly( img, buf, count, CV_RGB(rand()&255,rand()&255,rand()&255), CV_AA, 0 );
        //cvPolyLine( img, &buf, &count, 1, 1, CV_RGB(0,0,0), 1, CV_AA, 0);
       // draw_subdiv_point( img, pt->pt, CV_RGB(0,200,200));
    }
    free( buf );
}

//drawing voronoi parts and getting Delaunay triangles 
void paint_voronoi( CvSubdiv2D* subdiv, IplImage* img )
{
	
	CvQuadEdge2D* outer_qedges[3];
    CvSeqReader  reader;
    int i, total = subdiv->edges->total;
	triangle = new TRIANGLE[total];
    int elem_size = subdiv->edges->elem_size;

    cvCalcSubdivVoronoi2D( subdiv );

    cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );

    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);
		
        if( CV_IS_SET_ELEM( edge ))
        {
            CvSubdiv2DEdge e = (CvSubdiv2DEdge)edge;
			CvSubdiv2DEdge e1 = (CvSubdiv2DEdge)edge;
			CvSubdiv2DEdge e2 = (CvSubdiv2DEdge)edge;

			CvSubdiv2DEdge eR = (CvSubdiv2DEdge)edge;
			CvSubdiv2DEdge eR1 = (CvSubdiv2DEdge)edge;
			CvSubdiv2DEdge eR2 = (CvSubdiv2DEdge)edge;
			//Left 
			//e
            e  = cvSubdiv2DGetEdge(e,CV_NEXT_AROUND_LEFT);	
			//eLnext
		    e1 = cvSubdiv2DGetEdge(e,CV_NEXT_AROUND_LEFT);
			//eOnext
			e2 = cvSubdiv2DGetEdge(e1,CV_NEXT_AROUND_LEFT);
			
		
			if((cvSubdiv2DEdgeOrg(e)->pt.x >0)&&(cvSubdiv2DEdgeOrg(e)->pt.y >0)){
				if((cvSubdiv2DEdgeOrg(e1)->pt.x >0)&&(cvSubdiv2DEdgeOrg(e1)->pt.y >0)){
					if((cvSubdiv2DEdgeOrg(e2)->pt.x >0)&&(cvSubdiv2DEdgeOrg(e2)->pt.y >0)){

						triangle[nombre_triangles].a = cvSubdiv2DEdgeOrg(e)->pt;
						triangle[nombre_triangles].b = cvSubdiv2DEdgeOrg(e1)->pt;
						triangle[nombre_triangles].c = cvSubdiv2DEdgeOrg(e2)->pt;
					  
			
						/*	cout <<endl<<endl<<"  e X:"<< cvSubdiv2DEdgeOrg(e)->pt.x <<"y :" <<cvSubdiv2DEdgeOrg(e)->pt.y << endl;
						    cout <<"  e1 X:"<< cvSubdiv2DEdgeOrg(e1)->pt.x <<"y :" <<cvSubdiv2DEdgeOrg(e1)->pt.y << endl;
							cout <<"  e2 X:"<< cvSubdiv2DEdgeOrg(e2)->pt.x <<"y :" <<cvSubdiv2DEdgeOrg(e2)->pt.y << endl;*/
							
							
							 nombre_triangles ++ ;
					}
				}
			}
			
		   
            // left
            draw_subdiv_facet( img, cvSubdiv2DRotateEdge( e, 1 ));
			//Right
			eR  = cvSubdiv2DGetEdge(e,CV_NEXT_AROUND_RIGHT);	
			//eLnext
		    eR1 = cvSubdiv2DGetEdge(e1,CV_NEXT_AROUND_RIGHT);
			//eOnext
			eR2 = cvSubdiv2DGetEdge(e2,CV_NEXT_AROUND_RIGHT);
			
			
            // right
            draw_subdiv_facet( img, cvSubdiv2DRotateEdge( e, 3 ));
        }

        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }
	
}

 //Optimisation of Delaunay Triangles and deleting repetition 
 void optimisation_delaunay_triangles(CvSubdiv2D* subdiv){
 int i , j ;
 i = 0;
 j = 0 ; 
 bool optimise  = false;

	 for ( i = 0 ; i< sizeof(triangle);i++){
	   	optimise = false ;
		for( j = 0 ; j < sizeof(triangle);j++){
		
		 //I doit étre different de j pour ne pas repeter le triangle courrant a comparer :  
			if((i!=j)&&(optimise == false)){
		 
			  //Test i les triangles ne se repetes pas : 
		if(((triangle[i].a.x!=triangle[j].a.x) || (triangle[i].a.x!=triangle[j].b.x) || (triangle[i].a.x!=triangle[j].c.x))
			&&((triangle[i].b.x!=triangle[j].a.x) || (triangle[i].b.x!=triangle[j].b.x) || (triangle[i].b.x!=triangle[j].c.x))
				 &&((triangle[i].c.x!=triangle[j].a.x) || (triangle[i].c.x!=triangle[j].b.x) || (triangle[i].c.x!=triangle[j].c.x))){
					 
		                  //   cout <<endl<< j << endl;
				   	cout<<endl <<triangle[i].a.x <<endl;
						  cout <<triangle[i].b.x <<endl;
						  cout <<triangle[i].c.x <<endl;

				     optimise = true ;
					
		    }
		 }
		}
	 }
 }

//Painting the construction of the tesellation 
 void Mypaint(CvSubdiv2D* subdiv,CvPoint2D32f *points2D,IplImage* img2,CvScalar bkgnd_color,char window_name2[],CvScalar delaunay_color,CvScalar active_facet_color,int i){  
	    locate_point(subdiv, points2D[i], img2, active_facet_color);
      	cvShowImage( window_name2, img2 );
		cvCalcSubdivVoronoi2D ( subdiv );
		cvSet( img2, bkgnd_color, 0 );
	    draw_subdiv( img2, subdiv, delaunay_color);  
          //if( cvWaitKey( 100 ) >= 0 )
          // break;
		//cvWaitKey(0);

 }

 //Call back all of the essentiel fonctions 
 void run(){
 
    data3d = lecturePoints3D(n_Points2D);
	dataDelaunay  = lecturePoints2D(n_Points2D);										 // Getting dataDelaunay points from the text file
	CvSubdiv2D* subdiv = init_delaunay( storage, init_Cv_Storage( 0 , 0 , w , h ));      // Creation of Delaunay subdivision
	subdiv = create_delaunay_subdivision( subdiv, dataDelaunay , n_Points2D );		     // Getting my finale_subdiv                               
	//create_file_txt_delaunay2D_perfect(subdiv);
	paint_voronoi( subdiv, img );														 //
	cvSet( img, bkgnd_color, 0 );
	draw_subdiv( img, subdiv, delaunay_color);
	// optimisation_delaunay_triangles(subdiv);
    tri_triangles();
	//construction_Triangulation_ecriture_STL(subdiv);									 // Creating of my STL file with 3D triangulation
	construction_Triangulation_Delaunay2D_STL();
	cvClearSubdivVoronoi2D( subdiv );                                                    // Clearing voronoi From Subdiv "CvSubdiv2DPoint"
	cvNamedWindow("window");
	cvShowImage("window",img); 											 
	cvWaitKey();
 
 
 }



