#ifndef M_H
#define M_H

#include "efanna2e/index.h"

inline std::vector<std::vector<uint32_t>> read_fbin(const char* filename, uint32_t& npts, uint32_t& k_dim) {
    std::ifstream in(filename, std::ios::binary);
    in.read((char *)&npts, sizeof(npts));
    in.read((char *)&(k_dim), sizeof(k_dim));
    std::cout << "learn base knn npts: " << npts << ", k_dim: " << k_dim << std::endl;
    std::vector<std::vector<uint32_t>> learn_base_knn_;
    learn_base_knn_.resize(npts);
    for (uint32_t i = 0; i < npts; i++) {
        learn_base_knn_[i].resize(k_dim);
        in.read((char *)learn_base_knn_[i].data(), sizeof(uint32_t) * k_dim);
    }
    if (learn_base_knn_.back().size() != k_dim) {
        throw std::runtime_error("learn base knn file error");
    }
    in.close();
    return learn_base_knn_;
}

class HopcroftKarp {
   public:
    std::vector<uint32_t> pairU;

    HopcroftKarp(uint32_t m, uint32_t n, uint32_t dim, std::vector<std::vector<uint32_t>>& gt)
        : m_(m), n_(n), k_(dim), gt_(gt){};

    void match();

    void saveMatch(const char *filename);

   private:
    const int m_;
    const int n_;
    const int k_;
    const std::vector<std::vector<uint32_t>> gt_;

    bool bfs(uint32_t m);

    bool dfs(uint32_t u);

    uint32_t hopcroftKarp(uint32_t m, uint32_t n);

    std::vector<std::vector<uint32_t>> adj;
    std::vector<uint32_t> pairV, dist;
};

#endif  // M_H