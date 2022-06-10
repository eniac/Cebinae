action aiEstimate_log_rate_head(bit<8> log_v) {log_rate_head = log_v;}
table tiEstimate_log_rate_head {
    key = { rate_head : ternary; }
    action = { aiEstimate_log_rate_head }
	const entries = {
		(1 &&& 1) : aiEstimate_log_rate_head(0);
		(2 &&& 2) : aiEstimate_log_rate_head(1);
		(4 &&& 4) : aiEstimate_log_rate_head(2);
		(8 &&& 8) : aiEstimate_log_rate_head(3);
		(16 &&& 16) : aiEstimate_log_rate_head(4);
		(32 &&& 32) : aiEstimate_log_rate_head(5);
		(64 &&& 64) : aiEstimate_log_rate_head(6);
		(128 &&& 128) : aiEstimate_log_rate_head(7);
		(256 &&& 256) : aiEstimate_log_rate_head(8);
		(512 &&& 512) : aiEstimate_log_rate_head(9);
		(1024 &&& 1024) : aiEstimate_log_rate_head(10);
		(2048 &&& 2048) : aiEstimate_log_rate_head(11);
		(4096 &&& 4096) : aiEstimate_log_rate_head(12);
		(8192 &&& 8192) : aiEstimate_log_rate_head(13);
		(16384 &&& 16384) : aiEstimate_log_rate_head(14);
		(32768 &&& 32768) : aiEstimate_log_rate_head(15);
		(65536 &&& 65536) : aiEstimate_log_rate_head(16);
		(131072 &&& 131072) : aiEstimate_log_rate_head(17);
		(262144 &&& 262144) : aiEstimate_log_rate_head(18);
		(524288 &&& 524288) : aiEstimate_log_rate_head(19);
		(1048576 &&& 1048576) : aiEstimate_log_rate_head(20);
		(2097152 &&& 2097152) : aiEstimate_log_rate_head(21);
		(4194304 &&& 4194304) : aiEstimate_log_rate_head(22);
		(8388608 &&& 8388608) : aiEstimate_log_rate_head(23);
		(16777216 &&& 16777216) : aiEstimate_log_rate_head(24);
		(33554432 &&& 33554432) : aiEstimate_log_rate_head(25);
		(67108864 &&& 67108864) : aiEstimate_log_rate_head(26);
		(134217728 &&& 134217728) : aiEstimate_log_rate_head(27);
		(268435456 &&& 268435456) : aiEstimate_log_rate_head(28);
		(536870912 &&& 536870912) : aiEstimate_log_rate_head(29);
		(1073741824 &&& 1073741824) : aiEstimate_log_rate_head(30);
		(2147483648 &&& 2147483648) : aiEstimate_log_rate_head(31);
		_ : aiEstimateRateHeadLog(0);
	}
}