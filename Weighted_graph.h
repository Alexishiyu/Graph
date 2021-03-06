/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include <queue>
#include "Leftist_heap.h"
#include "ece250.h"
#include "Exception.h"
// include whatever classes you want

class Weighted_graph {
	private:
		// your implementation here
		//  you can add both private member variables and private member functions
	    double **matrixMap;
		int  *degreeArray; //Holds the number of degrees for each node
		int total_edges;
		int mapSize;
		static const double INF;
	    Leftist_heap<int>* queue;


	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here
//Constructor.
Weighted_graph::Weighted_graph( int size ){
	  if(size <= 0)
	      	{
	      		size = 1;
	      	}
      matrixMap  = new double * [size];
      degreeArray = new int[size];


      for(int i = 0; i < size; i++){
    	  matrixMap[i] = new double[size];
  		  degreeArray[i] = 0;

      }

      for(int i = 0; i < size; i++){
    	  for(int j = 0; j < size; j++){
    		  matrixMap[i][j] = INF;
    	  }
    	  matrixMap[0][0] = 0.0;

      }
      queue =new Leftist_heap<int>();
      total_edges = 0;
      mapSize = size;

}

Weighted_graph::~Weighted_graph( ){
	for(int i = 0; i < mapSize; i++){
	    delete [] matrixMap[i];
	  }
	delete [] matrixMap;
	delete [] degreeArray;
	delete queue;

}

int Weighted_graph:: edge_count() const{

	return total_edges;
}

int Weighted_graph:: degree(int n) const{
	if(n< 0 || n >= mapSize)
		{
			throw illegal_argument();
		}
	return degreeArray[n];
}

double Weighted_graph:: adjacent(int m, int n ) const{
	if(n<0 || n>= mapSize || m<0 || m>=mapSize)
		{
			throw illegal_argument();
		}
//	if(matrixMap[m][n] == INF)
//		{
//			return ;
//		}
	if(m==n)
			{
				return 0.0;
			}
	 return matrixMap[m][n];
}

double Weighted_graph::distance(int m, int n) const{
	int* isVisited = new int [mapSize];
	double* distances = new double [mapSize];
//	if ( degree(n) == 0 || degree(m) == 0) throw illegal_argument();
		//If m or n are invalid, throw exception.
	if(n<0 || n>= mapSize || m<0 || m>=mapSize)	{
			throw illegal_argument();
	}
	if(m ==n){

	 return 0.0;

	}


	for(int i = 0; i < mapSize; i++){
		distances[i] = INF;
		isVisited[i] = 0;
	}
	        int startNode = m;
	        int nextNode ;
	        int goalNode = n;
	        distances[startNode] = 0.0;

//	        if (degree(startNode) == 0) {
//
//	        	return INF;
//
//	        }  this causes memeory leak???



	        queue->push(startNode,distances[startNode]);

	        while (!queue->empty()) {

	            int nextNode = 	queue->top();

	            queue->pop();


	            if (nextNode == goalNode) break;

	            if ((isVisited[nextNode] == 1) ){//|| degree(nextNode) == 0){
	                continue;
	             }



				if(isVisited[nextNode]== 0) {
					isVisited[nextNode]= 1;
	                for(int j = 0; j< mapSize;j++){

	                	if( adjacent(nextNode,j) != INF){


	                	    if(isVisited[j] == 1){
	                		continue;
	                	   }

	                	   if (distances[nextNode] +  adjacent(nextNode,j) < distances[j] ) {

	                		distances[j] = distances[nextNode] +  adjacent(nextNode,j);
            		        queue->push(j,distances[j]);

 	 	 	 	 	       }
	                    }
	               }
	            }
	        }

	        double dis = distances[goalNode];
	       	delete [] distances;
	       	delete [] isVisited;

	       return dis;

}



void Weighted_graph:: insert(int m ,int n, double w) {
	if(n < 0 || n >= mapSize || m < 0 || m >= mapSize || m == n || w <= 0)
		{
			throw illegal_argument();
		}


		if(matrixMap[m][n] == INF)
		{
			total_edges ++;
			degreeArray[n] ++;
			degreeArray[m] ++;
		}

		matrixMap[m][n] = w;
		matrixMap[n][m] = w;

}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
