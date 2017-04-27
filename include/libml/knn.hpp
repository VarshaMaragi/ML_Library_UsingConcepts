#ifndef LIBML_KNN_H
#define LIBML_KNN_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <numeric>
#include <vector>
#include "naive_bayes.hpp"

namespace libml {
        class KNN
        {
                public:

                        //using datatype=data1;
                        //using labelstype=labels;

                        using Data_type = libml::matrix2<int>;
                        using Label_type = std::vector<int>;

                        Data_type d;
                        Label_type l;
                        int k;
                        std::vector<int> predy;

                        //DataforClassification d=new DataforClassification();
                        //LabelsforClassification l= new LabelsforClassification();

                        void train(Data_type& x, Label_type& y)
                        {
                                if (x.size() != y.size())
                                {
                                        throw std::invalid_argument( "No. of rows in Train data and Train Labels must be equal");
                                }
                                std::cout<<"Knn training is trivial"<<std::endl;
                        };

                        std::vector<int> classify(Data_type& testdata)
                        {
                                std::ofstream f;
                                f.open ("outputknn.txt");
                                Data_type x = d;
                                int numberoffeatures=x[0].size();
                                int numberofexamples=x.size();


                                /*cout<<"Data size"<<x[0].size();
                                  for(int i=0;i<numberofexamples;i++)
                                  {
                                  for(int j=0;j<numberoffeatures;j++)
                                  {
                                  cout<<x[i][j]<<" ";
                                  }
                                  cout<<endl;
                                  }*/

                                std::vector<int> predy;
                                std::vector<int> y=l;
                                for(int j=0;j<testdata.size();j++)
                                {

                                        std::vector<double> eucdist;

                                        //Given one testdata it calculates the Euclidean distance between the given test data and 
                                        //the rest of the example.

                                        for(int i=0;i<numberofexamples;i++)
                                        {
                                                std::vector<double> dist;
                                                std::transform(x[i].begin(), x[i].end(), testdata[j].begin(), std::back_inserter(dist),
                                                                [&](int a, int b) { return ((a-b)*(a-b)); });

                                                int sum = std::accumulate(dist.begin(), dist.end(), 0);
                                                eucdist.push_back(sqrt(sum));


                                        }

                                        //sort the euclidean distances in ascending order using a vector of pairs
                                        std::vector<std::pair<int,int>> peuc;
                                        for(int i=0;i<eucdist.size();i++)
                                        {
                                                peuc.push_back(std::make_pair(eucdist[i], i));

                                        }

                                        sort(peuc.begin(),peuc.end());

                                        int classy=0;
                                        for(int i=0;i<k;i++)
                                        {
                                                //Take the classy of the first k values
                                                classy=classy+(y[peuc[i].second]);
                                        }

                                        //Assuming the classes are 1 and -1
                                        if(classy>0)
                                                predy.push_back(1);
                                        else
                                                predy.push_back(-1);
                                }


                                //Print the predicted y values
                                std::cout<<"KNN predicted values"<<std::endl;
                                for(int j=0;j<predy.size();j++)
                                {
                                        std::cout<<predy[j];
                                }

                                return predy;
                        };

        };
} // namespace libml

#endif // ifndef LIBML_KNN_H
