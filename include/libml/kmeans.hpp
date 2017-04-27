#include <vector>
#include <stdlib.h>
#include <limits>
#include <algorithm>
#include "helper.hpp"

using namespace std;

class KMeans{
private:
	int k;
	double maxIter;

public:

	vector<vector<double>> init_centroids(vector<vector<double>>& train_data)
	{
		vector<vector<double>> centroids;
		for (int i = 0; i < k; i++)
		{
			auto n = rand() % train_data.size();
			// cout << n << endl;
			centroids.push_back(train_data[n]);
		}
		return centroids;
	}

    //  # Calculate new centroids as the means of the samples
    // # in each cluster
    // def _calculate_centroids(self, clusters, X):
    //     n_features = np.shape(X)[1]
    //     centroids = np.zeros((self.k, n_features))
    //     for i, cluster in enumerate(clusters):
    //         centroid = np.mean(X[cluster], axis=0)
    //         centroids[i] = centroid
    //     return centroids

    vector<double> cluster_mean(vector<vector<double>> cluster)
    {
    	vector<double> clmean(cluster[0].size(), 0);
		for (int j = 0; j < cluster[0].size(); j++)
		{
			for (int i = 0; i < cluster.size(); i++)
			{
				clmean[j] += cluster[j][i];
			}
			clmean[j] /= cluster.size();
		}
		return clmean;
    }

	vector<vector<double>> calculate_centroids(auto clusters, vector<vector<double>>& train_data)
	{	
		int n_features = train_data[0].size();
		vector<vector<double>> centroids(k, vector<double>(n_features));
		for (int i = 0; i < k; i++)
		{
			auto centroid = cluster_mean(clusters[i]);
			centroids[i] = centroid;
		}
		return centroids;
	}
	
	int closest_centroid(auto& sample, auto& centroids)
	{
		double closest_distance = std::numeric_limits<double>::infinity();
		int closest_i = 0;
		for (int i = 0; i < centroids.size(); i++)
		{
			auto distance = euclidean_distance(sample, centroids[i]);
			if (distance < closest_distance)
			{
				closest_i = i;
				closest_distance = distance;
			}
		}
		return closest_i;
	}
	
	vector<vector<vector<double>>> create_clusters(vector<vector<double>>& centroids, vector<vector<double>>& train_data)
	{
		auto n_samples = train_data.size();
		vector<vector<vector<double>>> clusters(3);

		for (auto sample : train_data)
		{
			int centroid_i = closest_centroid(sample, centroids);
			clusters[centroid_i].push_back(sample);
		}
		return clusters;
	}

	bool diff(auto centroids, auto prev_centroids)
	{
		for (auto c1: centroids)
		{
			int flag = 0;
			for (auto c2 : prev_centroids)
			{
				if (c1 == c2)
				{
					flag = 1;
				}
			}
			if (flag == 0)
			{
				return 1;
			}
		}
		return 0;
	}

	vector<int> cluster_labels(auto clusters,auto train_data)
	{
		vector<int> pred_labels;
		for (auto ex : train_data)
		{
			for (int i = 0; i < clusters.size(); i++)
			{
				for (auto elem : clusters[i])
				{
					if (elem == ex)
					{
						pred_labels.push_back(i);
					}

				}
			}
		}
		return pred_labels;
	}

	vector<int> classify(vector<vector<double>>& train_data)
	{
		vector<vector<double>> centroids = init_centroids(train_data);
		vector<vector<double>> prev_centroids;
		int iter = 1;
		vector<vector<vector<double>>> clusters;
		
		while(iter <= maxIter)
		{
			clusters = create_clusters(centroids, train_data);
			prev_centroids = centroids;

			centroids = calculate_centroids(clusters, train_data);
			if (diff(centroids, prev_centroids))
			{
				break;
			}

//    # Calculate new centroids as the means of the samples
// 	# in each cluster
// 	def _calculate_centroids(self, clusters, X):
//     n_features = np.shape(X)[1]
//     centroids = np.zeros((self.k, n_features))
//     for i, cluster in enumerate(clusters):
//         centroid = np.mean(X[cluster], axis=0)
//         centroids[i] = centroid
//     return centroids
		}

		return cluster_labels(clusters, train_data);
	}

	KMeans(int k = 3, double maxIter = 100)
	: k(k), maxIter(maxIter)
	{}
};