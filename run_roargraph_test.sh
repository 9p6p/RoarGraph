cd build

prefix=/root/autodl-tmp/datasets/t2i-10M
saveprefix=/root/autodl-tmp/indices/t2i-10M

./tests/test_build_roargraph --data_type float --dist ip \
--base_data_path ${prefix}/base.10M.fbin \
--sampled_query_data_path ${prefix}/query.train.10M.fbin \
--projection_index_save_path ${saveprefix}/t2i_10M_bipartiteddd.index \
--learn_base_nn_path ${prefix}/gt.train.10M.ibin \
--M_sq 100 --M_pjbp 35 --L_pjpq 500 -T 10