num_threads=1
topk=10

cd build

prefix=/root/autodl-tmp/datasets/t2i-10M
indices=/root/indices/t2i-10M
results=/root/results/t2i-10M
graph=t2i_10M_roar_query_10M_pure_matchk100_epmost.index

./tests/test_search_roargraph --data_type float \
--dist ip --base_data_path ${prefix}/base.10M.fbin \
--projection_index_save_path ${indices}/${graph} \
--gt_path ${prefix}/gt.10k.ibin  \
--query_path ${prefix}/query.10k.fbin \
--L_pq 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 110 120 130 140 150 160 170 180 190 200 220 240 260 280 300 350 400 450 500 550 600 650 700 750 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 \
--k ${topk}  -T ${num_threads} \
--ep_point "3030517" \
--evaluation_save_path ${results}/searchtest_${graph}_top${topk}_T${num_threads}.csv
#   8570501   3030517  "-1"