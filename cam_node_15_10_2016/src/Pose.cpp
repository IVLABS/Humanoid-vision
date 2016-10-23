



#include "Pose.h"


Pose::Pose()
    {
        
        objectPoints1.push_back(cv::Point3f( -0.090f,0.090f,0.0f));
	objectPoints1.push_back(cv::Point3f(-0.090f,-0.090f,0.0f));
 	objectPoints1.push_back(cv::Point3f(0.090f,-0.090f,0.0f));
  	objectPoints1.push_back(cv::Point3f(0.090f,0.090f,0.0f));
  
        objectPoints2.push_back(cv::Point3f( 0.090f,0.090f,0.0f));
	objectPoints2.push_back(cv::Point3f(-0.090f,0.090f,0.0f));
 	objectPoints2.push_back(cv::Point3f(-0.090f,-0.090f,0.0f));
  	objectPoints2.push_back(cv::Point3f(0.090f,-0.090f,0.0f));
  

       
        cameraIntrinsicParams=Mat(Size(3,3),CV_64FC1);
       
       cameraIntrinsicParams.at<double>(0,0)= 733.0519551883676;
	cameraIntrinsicParams.at<double>(0,1)= 0.0;
	cameraIntrinsicParams.at<double>(0,2)= 308.59827311435;
	cameraIntrinsicParams.at<double>(1,0)= 0 ;
	cameraIntrinsicParams.at<double>(1,1)= 735.1820471505564;
	cameraIntrinsicParams.at<double>(1,2)= 228.4401120706685;
	cameraIntrinsicParams.at<double>(2,0)= 0.0 ;
	cameraIntrinsicParams.at<double>(2,1)= 0.0 ;
	cameraIntrinsicParams.at<double>(2,2)= 1.0 ;

     
//    distCoeffs=Mat::zeros(Size(1,5),CV_32FC1);
      distCoeffs=Mat(Size(1,5),CV_64FC1);
       distCoeffs.at<double>(0,0)=0.05473006817446581;
       distCoeffs.at<double>(0,1)=-0.4169723577175724;
       distCoeffs.at<double>(0,2)=0.0002363503817115325;
       distCoeffs.at<double>(0,3)=0.002502402742858189;
       distCoeffs.at<double>(0,4)=0.000000;

      
 
    }



double* Pose::contour_detection(Mat threshold,Mat threshold_extract ,Mat gray_src, Mat src)
{
   	int flag =0;
   	double largest_area=0.0;
   	int largest_contour_index=0;
        static double *location;  
        static double check[]={0.0,0.0,0.0,0.0,0.0,0.0} ;
        int j=0;
        int index[100];
        double area_array[100];  //area array
        int sum = 0;    
        double d;//distance
        int y=0;//sort
       int q=0;
        int lowThreshold=300;
   		int ratio=5;
  		int kernel_size=5;
   	vector<Point>Points ;
   	vector< vector<Point> > contours; // Vector for storing contour
   	vector<Vec4i> hierarchy1;
        vector<Vec4i> hierarchy2;
        vector<Vec4i> hierarchy3;
  	vector< vector<Point> > contours0;
        vector< vector<Point> > contours1;
        vector< vector<Point> > contours2;
    
        findContours( threshold, contours0, hierarchy1,CV_RETR_LIST,CV_CHAIN_APPROX_NONE); // Find the contours in the image
	

	contours.resize(contours0.size());
       
 	std::vector<Point2f> imagePoints;
        std::vector<Point2f> preciseCorners(4);
      
        
      
        int k=0 ;   
        
       
    	for( k=0; k < contours0.size(); k++ )
        {    
               
               double eps = contours0[k].size() * 0.05; 
		approxPolyDP(contours0[k], contours[k],eps, true);
          
              if (contours[k].size() != 4)
		continue;

                if (!cv::isContourConvex(contours[k]))
		continue;
                
                for(int m = 0; m < 4; m++) 
		{
                 d = (double)(contours[k][m].x - contours[k][(m + 1) % 4].x) *(double)(contours[k][m].x - contours[k][(m + 1) % 4].x) +
                       	   (double)(contours[k][m].y - contours[k][(m + 1) % 4].y) *(double)(contours[k][m].y - contours[k][(m + 1) % 4].y);
            
       		}
                
                if (d < 10)
                continue;

		
    	/*	for (unsigned int i = 0; i < contours[index[k]].size(); i++) 
		{

       		 int i2 = (i + 1) % contours[index[k]].size();
		 sum += sqrt((contours[index[k]][i].x - contours[index[k]][i2].x) * (contours[index[k]][i].x - contours[index[k]][i2].x) +(contours[index[k]][i].y - contours[index[k]][i2].y) * (contours[index[k]][i].y - contours[index[k]][i2].y));
  			
		 }
              
		if(sum < 100)
                continue;
          */    
                if(contours[k].size()==4)
		{
		
		index[j]=k;
                j=j+1;
                 
		}
                
       }
     
		if (contours0.size()==0)
		{             
		return check;
		}
  
/*	if(j>1)
	{
               Point2f quad_pts[4];
    	               Point2f squre_pts[4];
		if(p>=0)
		{          
                        cout<< "a"<<endl;
                       
                        cout<<"b"<<endl;         
                	Rect boundRect=boundingRect(contours[index[p]]);
	
                	quad_pts[0]=Point(contours[index[p]][0].x,contours[index[p]][0].y);
    			quad_pts[1]=Point(contours[index[p]][1].x,contours[index[p]][1].y);
    			quad_pts[2]=Point(contours[index[p]][2].x,contours[index[p]][2].y);
    			quad_pts[3]=Point(contours[index[p]][3].x,contours[index[p]][3].y); 
                        cout<<"c"<<endl;
                	squre_pts[0]=Point(boundRect.x,boundRect.y);
                        squre_pts[1]=Point(boundRect.x,boundRect.y+boundRect.height);
                        squre_pts[2]=Point(boundRect.x+boundRect.width,boundRect.y+boundRect.height);
                	squre_pts[3]=Point(boundRect.x+boundRect.width,boundRect.y);
                	
   			
    		 cout<<""<<endl;
               Mat transmtx = getPerspectiveTransform(quad_pts,squre_pts);  
              
    		 Mat transformed = Mat::zeros(threshold_id.rows, threshold_id.cols, CV_8UC1);	
 		warpPerspective(threshold_id, transformed, transmtx, threshold_id.size());               
                rectangle(transformed,boundRect,Scalar(0,255,0),1,8,0);
                //imshow("trsanformed",transformed);
                
		Mat marker=transformed(boundRect);
              // imshow("Marker",marker);
               




  
                for(int p = j-1;p>=0;p--)
		{
		
		Mat marker=threshold(Rect(Point(contours[index[p]][0].x,contours[index[p]][0].y),Point(contours[index[p]][2].x,contours[index[p]][2].y)));
		

		cv::Mat bitMatrix = cv::Mat::zeros(4,4,CV_8UC1);
                      
              int width = marker.cols / 4;
	      int height = marker.rows / 4;
              Mat cell;

		for(int y=0; y<=(marker.rows - height); y+=height)
		{
    			for(int x=0; x<=(marker.cols - width); x+=width)
   			 {
        			
				cell = marker(Rect(x, y, width, height));
        			int nZ = cv::countNonZero(cell);
				if (nZ> (width * height)/1.5)
				bitMatrix.at<uchar>(y,x) = 1;       			              
                                cout<<"bit Matrix "<<int(bitMatrix.at<uchar>(y,x))<<endl;
  			 }
		}


              			if(int(bitMatrix.at<uchar>(0,0)) == 1 && int(bitMatrix.at<uchar>(1,1)) == 0 && int(bitMatrix.at<uchar>(2,2)) == 0 && int(bitMatrix.at<uchar>(3,3)) == 1 )

             			 {

		
                                	for (int c=0;c<4;c++)
					{		
					preciseCorners[c] = contours[index[p]][c];
					}
         	
                			//cv::cornerSubPix(threshold,preciseCorners, cvSize(15,15),cvSize(-1,-1),  
					//TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
                                     
					cv::cornerSubPix(threshold, preciseCorners, cvSize(8,8),cvSize(-1,-1), 
					cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));
                						
				
                			for (int c=0;c<4;c++)
					{
					contours[index[p]][c] = preciseCorners[c];
					}
                         
      					imagePoints.push_back(Point2f(contours[index[p]][0].x,contours[index[p]][0].y));
    					imagePoints.push_back(Point2f(contours[index[p]][1].x,contours[index[p]][1].y));
    					imagePoints.push_back(Point2f(contours[index[p]][2].x,contours[index[p]][2].y));
    					imagePoints.push_back(Point2f(contours[index[p]][3].x,contours[index[p]][3].y));
		                       
                                       
          				Point P1=contours[index[p]][0];
    					Point P2=contours[index[p]][1];
    					Point P3=contours[index[p]][2];
   					Point P4=contours[index[p]][3];

    					line(src,P1,P2, Scalar(0,0,255),0,CV_AA,0);
			    		line(src,P2,P3, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P3,P4, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P4,P1, Scalar(0,0,255),0,CV_AA,0);
                
               				location=pose_estimation(objectPoints,imagePoints);
                                        
					return location;  
                		}
                     p=p-1;                      		              
        	}	   	
	
	}
*/

if(j>2)
	{
                
		
		for( int i = 0; i<j; i++ )
		{           
                    area_array[i]=contourArea( contours[index[i]],false);
                  
		}  
                
               for (int s=1 ; s < j ; s++)
                      
		{
                  
	              for (int r=s; r<=j-1; r++)
                        
                         {
                        
			 double ratio=area_array[j-s]/area_array[j-(r+1)];
                          
                          
                         	if(ratio> 6.0 && ratio <8.0 )	
                                 {
			       //  cout<<" area "<< area_array[j-s] << endl;
				// cout<<"ratio"<< ratio << endl;	
                             	 q=j-s;
/*                              	 Mat marker,black ;
                               		if(contours[index[q]].size()==4)	
                              		{
			      		Rect boundRect=boundingRect(contours[index[q]]);

                            		
	                                        if((boundRect.x - 10) >= 0 && (boundRect.y - 10) >= 0 && (boundRect.x + boundRect.width + 20) < threshold.cols && (boundRect.y+ boundRect.height + 20) < threshold.rows)
	                                         {

		              Point A(boundRect.x - 10 ,boundRect.y - 10) ;	
                              Point B(boundRect.x + boundRect.width + 20 ,boundRect.y+  boundRect.height + 20);                                
                              		marker=gray_src(Rect(A,B));
                                        black = Mat::ones(Size(src.cols, src.rows), CV_8UC1);
                                        marker.copyTo(black(Rect(A,B)));
                              //		imshow("marker", black);

			      		//cv::adaptiveThreshold(marker,marker,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,7,7);
            	              
                             		 Canny(marker,marker, lowThreshold, lowThreshold*ratio, kernel_size );
                              		dilate( marker,marker, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
                              		erode(marker,marker, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                                        Canny(black,black, lowThreshold, lowThreshold*ratio, kernel_size );
                              		dilate( black,black, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
                              		erode(black,black, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                                   //     imshow("black",black);
       		                   //     imshow("adaptive",marker);
       		                        findContours( marker, contours1, hierarchy2,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
                                      
                                        findContours(black, contours2, hierarchy3,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
                              
                            	//       cout<<" MARKER SIZE  "<< contours1.size() <<endl;

                                     for(int j=0; j< contours2.size();j++)

                                       {
                                      // area_array[j]=contourArea( contours2[j],false);
                                       
                                       ///cout<<"area contour black : "<< area_array[j]<< endl;
                                       cout<<" corners : "<< contours2[j].size() << endl;
                                       }
				
                            	       for( int i = 0; i<contours1.size(); i++ )
			         	{           
              		     	        area_array[i]=contourArea( contours1[i],false);
                                  	
						if(area_array[i] >largest_area)
	          			 	{
 		  		 		largest_area=area_array[i];
    		  		 		
                                		}
                                 
					//cout<<"area contour marker"<< area_array[i]<< endl;
					} 
                                        
                            
                        
                                         for (int l=0 ;l < contours2.size() ; l++)
					{
					 area_array[l]=contourArea( contours2[l],false);
 
                                        	if (largest_area == area_array[l])
                                           		largest_contour_index=l;
                                  		
					}

					
					// double eps1 = contours2[largest_contour_index].size() * 0.05; 
		                         approxPolyDP(contours2[largest_contour_index], contours2[largest_contour_index],9, true);
                                      
					cout<<" corner "<<contours2[largest_contour_index].size()<<endl;
                                         cout<<"index "<< largest_contour_index<< endl;          


					for (int c=0;c<4;c++)
					{		
					preciseCorners[c] = contours2[largest_contour_index][c];
					}
         	
                			//cv::cornerSubPix(threshold,preciseCorners, cvSize(8,8),cvSize(-1,-1),  
					//TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
                                     
					cv::cornerSubPix(gray_src, preciseCorners, cvSize(5,5),cvSize(-1,-1), 
					cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER,30,0.1));
                					
				      
                			for (int c=0;c<4;c++)
					{
					contours2[largest_contour_index][c] = preciseCorners[c];
					}
                         

                                        
                                       
      					imagePoints.push_back(Point2f(contours2[largest_contour_index][0].x,contours2[largest_contour_index][0].y));
    					imagePoints.push_back(Point2f(contours2[largest_contour_index][1].x,contours2[largest_contour_index][1].y));
    					imagePoints.push_back(Point2f(contours2[largest_contour_index][2].x,contours2[largest_contour_index][2].y));
    					imagePoints.push_back(Point2f(contours2[largest_contour_index][3].x,contours2[largest_contour_index][3].y));
		                       
                                        cout<<" X :"<< contours2[largest_contour_index][0].x <<  " Y : "<< contours2[largest_contour_index][0].y<<endl;
                                      
				        cout<<" X :"<< contours2[largest_contour_index][1].x <<  " Y : "<< contours2[largest_contour_index][1].y <<endl;			
					cout<<" X :"<< contours2[largest_contour_index][2].x <<  " Y : "<< contours2[largest_contour_index][2].y <<endl;
					cout<<" X :"<< contours2[largest_contour_index][3].x <<  " Y : "<< contours2[largest_contour_index][3].y <<endl;		
          				Point P1=contours2[largest_contour_index][0];
    					Point P2=contours2[largest_contour_index][1];
    					Point P3=contours2[largest_contour_index][2];
   					Point P4=contours2[largest_contour_index][3];

                                        

    					line(src,P1,P2, Scalar(0,0,255),0,CV_AA,0);
			    		line(src,P2,P3, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P3,P4, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P4,P1, Scalar(0,0,255),0,CV_AA,0);
                                         
                                      if (P2.y < P4.y)
                                        {
                                        cout<<"wrong"<<endl;
               				location=pose_estimation(objectPoints2,imagePoints); 
                                        return location;
                                        }
				     else 
                                       {

                                        cout<<"correct"<<endl;
					location=pose_estimation(objectPoints1,imagePoints); 
                                        return location;
					}
      
                                
                           
						 }
                                       else     
                                        return check;
                                        
					}
*/					

				    	for (int c=0;c<4;c++)
					{		
					preciseCorners[c] = contours[index[q]][c];
					}
         	
                			//cv::cornerSubPix(threshold,preciseCorners, cvSize(8,8),cvSize(-1,-1),  
					//TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
                                     
					cv::cornerSubPix(gray_src, preciseCorners, cvSize(5,5),cvSize(-1,-1), 
					cvTermCriteria(CV_TERMCRIT_ITER,30,0.1));
                					
				      
                			for (int c=0;c<4;c++)
					{
					contours[index[q]][c] = preciseCorners[c];
					}
                         

                                        
                                       
      					imagePoints.push_back(Point2f(contours[index[q]][0].x,contours[index[q]][0].y));
    					imagePoints.push_back(Point2f(contours[index[q]][1].x,contours[index[q]][1].y));
    					imagePoints.push_back(Point2f(contours[index[q]][2].x,contours[index[q]][2].y));
    					imagePoints.push_back(Point2f(contours[index[q]][3].x,contours[index[q]][3].y));
		                       
 /*                                       cout<<" X :"<< contours[index[q]][0].x <<  " Y : "<< contours[index[q]][0].y<<endl;
 					                                           
				        cout<<" X :"<< contours[index[q]][1].x <<  " Y : "<< contours[index[q]][1].y <<endl;			
					cout<<" X :"<< contours[index[q]][2].x <<  " Y : "<< contours[index[q]][2].y <<endl;
					cout<<" X :"<< contours[index[q]][3].x <<  " Y : "<< contours[index[q]][3].y <<endl;		
   */       				Point P1=contours[index[q]][0];
    					Point P2=contours[index[q]][1];
    					Point P3=contours[index[q]][2];
   					Point P4=contours[index[q]][3];

                                        

    					line(src,P1,P2, Scalar(0,0,255),0,CV_AA,0);
			    		line(src,P2,P3, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P3,P4, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P4,P1, Scalar(0,0,255),0,CV_AA,0);
                                         
                                      if (P2.y < P4.y)
                                        {
                                        //cout<<"wrong"<<endl;
               				location=pose_estimation(objectPoints2,imagePoints); 
                                        return location;
                                        }
				     else 
                                       {

                                        //cout<<"correct"<<endl;
					location=pose_estimation(objectPoints1,imagePoints); 
                                        return location;
					} 
 					

	        		}

			}
		}	
                                           		              
        }   		

return check;		
	            
}

double* Pose::pose_estimation(const std::vector<cv::Point3f> &objectPoints,const std::vector<cv::Point2f> &imagePoints)
{
       
        static double position[6];
	 
       Mat rvec,tvec,inliers;
/*cv::Mat_<double> rvec(cv::Size(3, 1));
    cv::Mat_<double> tvec(cv::Size(3, 1));
    rvec=0.0f;
    tvec=0.0f;
*/	bool useExtrinsicGuess =false; 
        int method = CV_ITERATIVE ;
	
cv::solvePnP(objectPoints,imagePoints, cameraIntrinsicParams,distCoeffs,rvec, tvec,useExtrinsicGuess,method);//distCoeffs
/* int iterationsCount = 500;        // number of Ransac iterations.
   	float reprojectionError = 8;    // maximum allowed distance to consider it an inlier.
    	float confidence = 0.95;          // ransac successful confidence.
    	int flags=0;
	cv::solvePnPRansac( objectPoints, imagePoints,cameraIntrinsicParams,distCoeffs,rvec,tvec,
                            useExtrinsicGuess, iterationsCount, reprojectionError, confidence,
                        inliers, flags );
 */
 /*for(int i=0 ; i <3 ; i++)
       {
        cout<<" rvec["<< i << "] : " << rvec.at<double>(i,0) << endl;
        cout<<" tvec["<< i << "] : " << tvec.at<double>(i,0) << endl;
       }  
   */   
      
        Mat J;
	vector<Point2f> p(3);
	projectPoints(objectPoints,rvec,tvec, cameraIntrinsicParams,distCoeffs, p, J);//distCoeffs
        float sum = 0.;
  	for (size_t i = 0; i <p.size(); i++)
         {
          sum += ((p[i].x - imagePoints[i].x)* (p[i].x - imagePoints[i].x)+(p[i].y - imagePoints[i].y)* (p[i].y - imagePoints[i].y));
         }
       
        Mat Sigma = Mat(J.t() * J, Rect(0,0,6,6)).inv();

// Compute standard deviation
	Mat std_dev;
	sqrt(Sigma.diag(), std_dev);
	//cout << "rvec, tvec standard deviation:" << endl << std_dev << endl;
 
  /*   for(int i =0;i<3 ;i++)
        {
        rvec.at<double>(i,0)=rvec.at<double>(i,0) - std_dev.at<double>(0,i) ;
        tvec.at<double>(i,0)=tvec.at<double>(i,0) - std_dev.at<double>(0,i+3) ;
       }
*/

       Mat distant=Mat(Size(3,3),CV_64FC1);
     	Mat jacobian=Mat(Size(3,1),CV_64FC1);

	Rodrigues(rvec,distant,jacobian);
        Mat R= distant.t(); 
    	
     	
               Mat T = -R * tvec ;
               
               
               cout << "error =" << sum << endl;
              
               position[0] =T.at<double>(0,0);
               position[1]=T.at<double>(1,0);
               position[2]=T.at<double>(2,0);
               position[3] = ((atan2(-R.at<double>(2,1), R.at<double>(2,2)))*180)/3.142;  //roll
	       position[4] = ((asin(R.at<double>(2,0)))*180)/3.142;                       //pitch
	       position[5] = ((atan2(-R.at<double>(1,0), R.at<double>(0,0)))*180)/3.142;   //yaw

               if (position[2] >0 && position[1] > 0 ) 
               {
	       return position;
               }        
        
}





