#ifndef LIBML_KMEANS_HPP
#define LIBML_KMEANS_HPP

#include <vector>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include "helpers.hpp"

namespace libml {

class KMeans{
private:
	int k;
	double maxIter;

public:

        using Data_type = libml::matrix2<double>;
        using Data_primitive = double;

        std::vector<std::vector<double>> init_centroids(std::vector<std::vector<double>>& train_data)
	{
                std::vector<std::vector<double>> centroids;
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

        std::vector<double> cluster_mean(std::vector<std::vector<double>> cluster)
    {
            std::vector<double> clmean(cluster[0].size(), 0);
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

        std::vector<std::vector<double>> calculate_centroids(auto clusters, std::vector<std::vector<double>>& train_data)
	{	
		int n_features = train_data[0].size();
                std::vector<std::vector<double>> centroids(k, std::vector<double>(n_features));
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
			auto distance = libml::euclidean_distance(sample, centroids[i]);
			if (distance < closest_distance)
			{
				closest_i = i;
				closest_distance = distance;
			}
		}
		return closest_i;
	}
	
        std::vector<std::vector<std::vector<double>>> create_clusters(std::vector<std::vector<double>>& centroids, std::vector<std::vector<double>>& train_data)
	{
		auto n_samples = train_data.size();
                std::vector<std::vector<std::vector<double>>> clusters(3);

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

        std::vector<int> cluster_labels(auto clusters,auto train_data)
	{
                std::vector<int> pred_labels;
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

        void train(Data_type& data) {
                // FIXME
                throw std::logic_error("Not implemented");
        }

        std::vector<int> classify(std::vector<std::vector<double>>& train_data)
	{
                std::vector<std::vector<double>> centroids = init_centroids(train_data);
                std::vector<std::vector<double>> prev_centroids;
		int iter = 1;
                std::vector<std::vector<std::vector<double>>> clusters;
		
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

} // namespace libml

#endif // ifndef LIBML_KMEANS_HPP
