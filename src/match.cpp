#include <match.h>
#include <limits.h>
#include <queue>

bool HopcroftKarp::bfs(uint32_t m) {
    std::queue<int> Q;
    for (uint32_t u = 0; u < m; ++u) {
        if (pairU[u] == -1) {
            dist[u] = 0;
            Q.push(u);
        } else {
            dist[u] = INT_MAX;
        }
    }

    dist[-1] = INT_MAX;

    while (!Q.empty()) {
        uint32_t u = Q.front();
        Q.pop();

        if (dist[u] < dist[-1]) {
            for (uint32_t v : adj[u]) {
                if (dist[pairV[v]] == INT_MAX) {
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }

    return (dist[-1] != INT_MAX);
}

bool HopcroftKarp::dfs(uint32_t u) {
    if (u != -1) {
        for (uint32_t v : adj[u]) {
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v]) == true) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INT_MAX;
        return false;
    }
    return true;
}

uint32_t HopcroftKarp::hopcroftKarp(uint32_t m, uint32_t n) {
    uint32_t result = 0;

    std::cout << "==== start match. ====  ";
    while (bfs(m)) {
        for (size_t u = 0; u < m; ++u) {
            if (pairU[u] == -1 && dfs(u)) {
                result++;
            }
        }
    }

    return result;
}

void HopcroftKarp::match() {
    unsigned MAX = m_ + 4;
    adj.resize(MAX);
    pairU.assign(MAX, -1);
    pairV.assign(MAX, -1);
    dist.assign(MAX, 0);

    std::cout << "nq: " << n_ << std::endl;

    for (size_t i = 0; i < m_; ++i) {
        adj[i].reserve(k_);
    }

    for (size_t i = 0; i < n_; ++i) {
        for (size_t j = 0; j < k_; ++j) {
            adj[i].push_back(gt_[i][j]);
        }
    }

    std::cout << "max match: " << hopcroftKarp(n_, m_) << std::endl;

    bool flag = 1;

    std::vector<int> datas(m_, -1);
    int cnt = 0;
    for (size_t u = 0; u < m_; ++u) {
        if (pairU[u] != -1) {
            cnt++;
            datas[pairU[u]]++;
            if (datas[pairU[u]] > 1)
                std::cerr << "match fail." << std::endl;
        }
    }
    std::cout << "cnt: " << cnt << std::endl;

    if (cnt != n_) flag = 0;

    if (!flag) {
        size_t left = 0, right = 0;
        while (left < m_) {
            if (pairU[left] == -1) {
                while (right < m_) {
                    if (pairV[right] == -1) {
                        pairU[left] = right;
                        pairV[right] = left;
                        break;
                    }
                    right++;
                }
            }
            left++;
        }

        cnt = 0;
        for (size_t u = 0; u < m_; ++u) {
            if (pairU[u] != -1) {
                cnt++;
                datas[pairU[u]]++;
                if (datas[pairU[u]] > 1) {
                    std::cerr << "match fail." << std::endl;
                    flag = 0;
                }
            }
        }

        cnt = 0;
        for (size_t u = 0; u < m_; ++u) {
            if (datas[u] != -1) {
                cnt++;
            } else
                flag = 0;
        }
    }

    if (flag) {
        std::cout << "==== match success. ==== " << cnt << std::endl;
        std::vector<std::vector<uint32_t>>().swap(adj);
        std::vector<uint32_t>().swap(pairV);
        std::vector<uint32_t>().swap(dist);
    }
    else {
        std::cout << "==== match fail. ==== " << cnt << std::endl;
    }
}

void HopcroftKarp::saveMatch(const char *filename) {
    std::ofstream out(filename, std::ios::binary);
    if (out.is_open())
        std::cout << "ready" << std::endl;
    out.write((char*)&n_, 4);
    for (size_t u = 0; u < n_; u++) {
        out.write((char*)&pairU[u], 4);
    }
    out.close();
}