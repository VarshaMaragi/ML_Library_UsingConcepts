/**
 * @file kmeans.hpp
 * @brief Contains the k-means implementation
 */

#ifndef LIBML_KMEANS_HPP
#define LIBML_KMEANS_HPP

#include <vector>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include "helpers.hpp"

namespace libml {

/**
 * @brief k-means clustering model
 *
 * K-means is an #UnsupervisedClassification algorithm used for partitioning
 * samples into clusters where each sample in a cluster averages to a mean
 * close to the value of the samples.
 */
class KMeans{
private:
        std::size_t k;
	double maxIter;

public:

        using Data_type = libml::matrix2<double>;
        using Data_primitive = double;

        /**
         * @brief Initializes random centroids for k-means
         *
         * Used when initializing the k-means model. Random means are
         * selected at first before creating clusters where samples
         * are associated with the nearest means until convergence.
         */
    std::vector<std::vector<double>> init_centroids(const Data_type& train_data)
	{
        std::vector<std::vector<double>> centroids;
		for (std::size_t i = 0; i < k; i++)
		{
			auto n = rand() % train_data.size();
			// cout << n << endl;
			centroids.push_back(train_data[n]);
		}
		return centroids;
	}

	/**
         * @brief Finds the mean of a cluster
         */
    std::vector<double> cluster_mean(const std::vector<std::vector<double>>& cluster)
    {
            std::vector<double> clmean(cluster[0].size(), 0);
		for (std::size_t j = 0; j < cluster[0].size(); j++)
		{
			for (std::size_t i = 0; i < cluster.size(); i++)
			{
				clmean[j] += cluster[j][i];
			}
			clmean[j] /= cluster.size();
		}
		return clmean;
    }

    /**
     * @brief Finds the new centroids of each cluster
     * @return A vector storing vectors of training data rows. Each higher-order vector is a centroid.
     */
    std::vector<std::vector<double>> calculate_centroids(const auto& clusters, const Data_type& train_data)
	{	
		int n_features = train_data[0].size();
                std::vector<std::vector<double>> centroids(k, std::vector<double>(n_features));
		for (std::size_t i = 0; i < k; i++)
		{
			auto centroid = cluster_mean(clusters[i]);
			centroids[i] = centroid;
		}
		return centroids;
	}
	
	/**
         * @brief Finds the closest centroid for a sample
         */
	int closest_centroid(const auto& sample, const auto& centroids)
	{
		double closest_distance = std::numeric_limits<double>::infinity();
		int closest_i = 0;
		for (std::size_t i = 0; i < centroids.size(); i++)
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

	/**
         * @brief Creates new clusters based on a set of centroids and training data
         * @return A vector of centroids
         * @see KMeans::calculate_centroids
         */
    std::vector<Data_type> create_clusters(const std::vector<std::vector<double>>& centroids, const Data_type& train_data)
	{
                std::vector<std::vector<std::vector<double>>> clusters(3);

		for (const auto& sample : train_data)
		{
			int centroid_i = closest_centroid(sample, centroids);
			clusters[centroid_i].push_back(sample);
		}
		return clusters;
	}

    /**
     * @brief Flags if two sets of centroids are divergent
     * @return true if the centroids differ, false otherwise
     */
	bool diff(const std::vector<std::vector<double>>& centroids, const std::vector<std::vector<double>>& prev_centroids)
	{
		for (const auto& c1: centroids)
		{
			int flag = 0;
			for (const auto& c2 : prev_centroids)
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
	
	/**
         * @brief Labels clusters corresponding to a set of training data
         * @return A vector of labels, each row corresponding to a row of training data
         */
    std::vector<int> cluster_labels(const std::vector<std::vector<std::vector<double>>>& clusters, const Data_type& train_data)
	{
                std::vector<int> pred_labels;
		for (const auto& ex : train_data)
		{
			for (std::size_t i = 0; i < clusters.size(); i++)
			{
				for (const auto& elem : clusters[i])
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

    /**
     * @brief Classifies a set of training data and returns a set of labels
     */
    std::vector<int> classify(const Data_type& train_data)
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
		}
		return cluster_labels(clusters, train_data);
	}

    /**
     * @brief Initializes the k-means model
     * @param k The number of means (clusters) to generate
     * @param maxIter The maximum number of iterations to run the model for
     *
     * @note
     * k-means is computationally expensive, especially on large datasets,
     * so maxIter should not be excessively large in an attempt to gain
     * more accuracy.
     */
	KMeans(std::size_t k = 3, double maxIter = 100)
	: k(k), maxIter(maxIter)
	{}
};

} // namespace libml

#endif // ifndef LIBML_KMEANS_HPP
