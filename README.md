# Image-Rotation-Project
  Rotating images by a given angle is a common image processing task. Although it seems little bit complicated, OpenCV provides some built-in functions making it easy to do it. Here is a simple OpenCV C++ example code to rotate an image. Here I use a track bar to change the rotating angle dynamically.
  
  ![road](https://user-images.githubusercontent.com/66546368/104435314-3ebc4e80-55b2-11eb-8f89-f2dada6e1569.jpg)          <img width="228" alt="Untitled" src="https://user-images.githubusercontent.com/66546368/104437489-d327b080-55b4-11eb-91f3-db4acba6397a.png">

# Rotation
  Rotating an image in OpenCV is accomplished by making a call to __Mat r=getRotationMatrix2D(pt,angle,1.0)__ and  __warpAffine(src, dst, r, bbox.size())__. Further care has to   betaken to supply the (x, y)-coordinate of the point the image is to be rotated about.
   To rotate an image, we need to know two things:\
   1.The center with respect to which the image will rotate.\
   2.The angle to be rotated. In OpenCV a positive angle is counter-clockwise.\
   3.Optional: A scale factor=1.0.
             
----
 __syntax__
 
    Point2f pt(src.cols / 2., src.rows / 2.);          
    Mat r = getRotationMatrix2D(pt, angle, 1.0);\
----
# Resizing and Transformation
  the roation matrix r maps the target to center. The bounding box bbox has a different center. The idea is to remove center from the translational component of the affine     transformation. The new center is the center of the bounding box bbox which is added.\

 __syntax__
       
       cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
	     // adjust transformation matrix
	     r.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
	     r.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;
----
   We now apply the found rotation to the output of our previous Transformation:\
    __syntax__
           
           cv::Mat dst;
           cv::warpAffine(src, dst, r, bbox.size());
----
# Displaying 
   Finally, we display our results in two windows plus the original image for good measure:\
   __syntax__
      
      imshow(windowname, dst);
	     waitKey(0);
	    destroyWindow(windowname);
    
  
