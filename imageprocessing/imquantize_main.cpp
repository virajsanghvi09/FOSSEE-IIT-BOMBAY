 /*Name : Viraj Sanghvi
    *function : imquantize
    *input argument : 'inputImage' is the input image.
    *output argument : 'quantizedImage' is the returned image
    *  with quantized levels.
    * 'levels' is an array of threholds
    * source : www.researchgate.net
    */
Mat imquantize(Mat inputImage, vector<vector<int> > levels)
{
    //initialise output label matrix
    Mat quantizedImage(inputImage.size(), inputImage.type(), Scalar::all(1));

    //Apply labels to the pixels according to the thresholds
    for (int m= 0; m < inputImage.cols; m++)
    {
        for (int i = 0;  < inputImage.rows; i++)
        {
            // Check if image is grayscale or BGR
            if(levels.size() == 1)
            {
                for (int p = 0; p < levels[0].size(); p++)
                {
                    // if pixel < lowest threshold , then assign 0
                    if(inputImage.at<uchar>(i,m) <= levels[0][0])
                    {
                        quantizedImage.at<uchar>(i,m) = 0;
                    }

                    // if pixel > highest threshold , then assign 255
                    else if(inputImage.at<uchar>(i,m) >= levels[0][levels[0].size()-1])
                    {
                        quantizedImage.at<uchar>(i,m) = 255;
                    }

                    // Check the level borders for pixel and assign the corresponding
                    // upper bound quanta to the pixel
                    else
                    {
                        if(levels[0][p] < inputImage.at<uchar>(i,m) && inputImage.at<uchar>(i,m) <= levels[0][p+1])
                        {
                            quantizedImage.at<uchar>(i,m) = (p+1)*255/(levels[0].size());
                        }
                    }
                }
            }

            else
            {
                Vec3b pair = inputImage.at<Vec3b>(i,m);

                // Processing the Blue Channel
                for (int p = 0; p < levels[0].size(); p++)
                {
                    if( pair.val[0] <= levels[0][0])
                    {
                        quantizedImage.at<Vec3b>(i,m)[0] = 0;
                    }
                    else if( pair.val[0] >= levels[0][levels.size()-1])
                    {
                        quantizedImage.at<Vec3b>(i,m)[0] = 255;
                    }
                    else
                    {
                        if(levels[0][p] < pair.val[0] && pair.val[0] <= levels[0][p+1])
                        {
                            quantizedImage.at<Vec3b>(i,m)[0] = (p+1)*255/(levels[0].size());
                        }
                    }
                }

                // Processing the Green Channel
                for (int p = 0; p < levels[1].size(); p++)
                {
                    if( pair.val[1] <= levels[1][0])
                    {
                        quantizedImage.at<Vec3b>(i,m)[1] = 0;
                    }
                    else if( pair.val[1] >= levels[1][levels.size()-1])
                    {
                        quantizedImage.at<Vec3b>(i,m)[1] = 255;
                    }
                    else
                    {
                        if(levels[1][p] < pair.val[1] && pair.val[1] <= levels[1][p+1])
                        {
                            quantizedImage.at<Vec3b>(i,m)[1] = (p+1)*255/(levels[1].size());
                        }
                    }
                }

                // Processing the Red Channel
                for (int p = 0; p < levels[2].size(); p++)
                {
                    if( pair.val[2] <= levels[2][0])
                    {
                        quantizedImage.at<Vec3b>(i,m)[2] = 0;
                    }
                    else if( pair.val[2] >= levels[2][levels.size()-1])
                    {
                        quantizedImage.at<Vec3b>(i,m)[2] = 255;
                    }
                    else
                    {
                        if(levels[2][p] < pair.val[2] && pair.val[2] <= levels[2][p+1])
                        {
                            quantizedImage.at<Vec3b>(i,m)[2] = (p+1)*255/(levels[2].size());
                        }
                    }
                }
            }
        }
    }
    return quantizedImage;
}
