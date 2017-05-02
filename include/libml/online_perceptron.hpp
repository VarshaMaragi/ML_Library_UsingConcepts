/**
 * @file online_perceptron.hpp
 * @brief Contains the online perceptron implementation
 */

#ifndef LIBML_ONLINE_PERCEPTRON_HPP
#define LIBML_ONLINE_PERCEPTRON_HPP

#include<stdio.h>

#include <iostream>
#include <numeric>
//#include "DataforClassification.h"
//#include "LabelsforClassification.h"
#include <fstream>
#include <sstream> 

#include "concepts.hpp"
#include "csv.hpp"

namespace libml {

        /**
         * @brief The online perceptron classifier
         *
         * The online version of the #Perceptron. Rather than
         * accepting a pre-created set of data during training,
         * the online perceptron accepts a stream of data and
         * continues to read from it until the stream is closed.
         *
         * Because the online perceptron is constantly adapting,
         * there is no dedicated method for training.
         *
         * @see OnlineLearningClassify
         */
        class OnlinePerceptron
        {
                public:


                        //Uses data as a stream of values
                        using Data_type=std::stringstream;
                        using Label_type=std::stringstream;

                        Data_type d;
                        Label_type l;

                        //Weights are calculated on the fly
                        std::vector<int> weights;

                        //Check if weights are initialized
                        bool initialised = 0;

                        /**
                         * @brief Trains the perceptron on a stream of data and stores classifications
                         */
                        void train(Data_type &x, Label_type &y)
                        {
                                std::string s;

                                //Convert stream to vector
                                std::vector<int> xvec;

                                while(getline(x, s, ','))
                                {
                                        xvec.push_back(stoi(s));

                                }

                                //The last element of the stream is the y value
                                int yvec=xvec[xvec.size()-1];

                                //Initialize the weights vector
                                if (!initialised)
                                {
                                        std::vector<int> temp(xvec.size(), 0);
                                        weights = temp;
                                        initialised=1;
                                }


                                //Append one		
                                xvec.insert(xvec.begin(),1);

                                //Remove the y value
                                xvec.pop_back();
                                int numberoffeatures=xvec.size();

                                if(yvec*(inner_product(begin(xvec), end(xvec), begin(weights), 0.0))<=0)
                                {
                                        for(int j=0;j<numberoffeatures;j++)
                                                weights[j]=weights[j]+yvec*xvec[j];

                                }

                                int j;

                                //Print the weights vector after every example
                                std::cout<<"----------Weights vector------------"<<std::endl;
                                for(j=0;j<numberoffeatures;j++)
                                {
                                        std::cout<<weights[j]<<",";
                                }
                                std::cout<<"-------------------------------------"<<std::endl;

                                //cout<<"train the model\n";
                        };

                        std::vector<int> classify(Data_type &x)
                        {
                                std::cout<<"Classification";
                        }
        };
} // namespace libml

#endif // ifndef LIBML_ONLINE_PERCEPTRON_HPP
