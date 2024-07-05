
prefix=./data/laion-10M
cp ./thirdparty/DiskANN/tests/utils/compute_groundtruth compute_groundtruth
mkdir -p ${prefix}

./compute_groundtruth --data_type float --dist_fn mips \
--base_file ${prefix}/base.10M.fbin  \
--query_file ${prefix}/query.train.10M.fbin  \
--gt_file ${prefix}/gt.query2query.10k.ibin --K 100