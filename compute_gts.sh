if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Please provide both dataset name and if query_train"
    exit 1
fi

dataset=$1
type=$2
prefix=./data/$dataset

if [ "$dataset" != "t2i-10M" ] && [ "$dataset" != "laion-10M" ] && [ "$dataset" != "clip-webvid-2.5M" ]; then
    echo "Invalid dataset name. Please choose from [t2i-10M, laion-10M, clip-webvid-2.5M]"
    exit 1
fi

cp /home/yuxiang/vector_data_graph/compre/RoarGraph/build/thirdparty/DiskANN/tests/utils/compute_groundtruth compute_groundtruth
mkdir -p ${prefix}

if [ "$type" == "false" ]; then
    if [ "$dataset" == "clip-webvid-2.5M" ]; then
        ./compute_groundtruth --data_type float --dist_fn mips \
        --base_file ${prefix}/base.2.5M.fbin  \
        --query_file ${prefix}/query.train.2.5M.fbin  \
        --gt_file ${prefix}/gt.train.2.5M.ibin --K 100
    else
        ./compute_groundtruth --data_type float --dist_fn mips \
        --base_file ${prefix}/base.10M.fbin  \
        --query_file ${prefix}/query.train.10M.fbin  \
        --gt_file ${prefix}/gt.train.10M.ibin --K 100
    fi
else
    if [ "$dataset" == "clip-webvid-2.5M" ]; then
        ./compute_groundtruth --data_type float --dist_fn mips \
        --base_file ${prefix}/query.train.2.5M.fbin  \
        --query_file ${prefix}/query.10k.fbin  \
        --gt_file ${prefix}/gt.query2query.10k.ibin --K 100
    else
        ./compute_groundtruth --data_type float --dist_fn mips \
        --base_file ${prefix}/query.train.10M.fbin  \
        --query_file ${prefix}/query.10k.fbin  \
        --gt_file ${prefix}/gt.query2query.10k.ibin --K 100
    fi
fi