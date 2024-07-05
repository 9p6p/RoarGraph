#include <match.h>

int main() {
    // m 和 n 分别是二分图两侧的节点数量
    unsigned m = 10000000, n, k;
    const char* filename = "/home/yuxiang/vector_data_graph/compre/RoarGraph/match";
    std::vector<std::vector<uint32_t>> gt = read_fbin("/home/yuxiang/vector_data_graph/compre/RoarGraph/data/t2i-10M/train.gt.bin", n, k);

    std::cout << n << "  " << k << std::endl;
    HopcroftKarp ho(m, n, k, gt);

    ho.match();
    ho.saveMatch(filename);
}