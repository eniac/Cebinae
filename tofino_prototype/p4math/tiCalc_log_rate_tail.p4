action aiCalc_log_rate_tail(bit<8> log_v) {log_rate_tail = log_v;}
table tiCalc_log_rate_tail {
    key = { rate_tail : ternary; }
    actions = { aiCalc_log_rate_tail; }
	const entries = {
		1 &&& 1 : aiCalc_log_rate_tail(0);
		2 &&& 2 : aiCalc_log_rate_tail(1);
		4 &&& 4 : aiCalc_log_rate_tail(2);
		8 &&& 8 : aiCalc_log_rate_tail(3);
		16 &&& 16 : aiCalc_log_rate_tail(4);
		32 &&& 32 : aiCalc_log_rate_tail(5);
		64 &&& 64 : aiCalc_log_rate_tail(6);
		128 &&& 128 : aiCalc_log_rate_tail(7);
		256 &&& 256 : aiCalc_log_rate_tail(8);
		512 &&& 512 : aiCalc_log_rate_tail(9);
		1024 &&& 1024 : aiCalc_log_rate_tail(10);
		2048 &&& 2048 : aiCalc_log_rate_tail(11);
		4096 &&& 4096 : aiCalc_log_rate_tail(12);
		8192 &&& 8192 : aiCalc_log_rate_tail(13);
		16384 &&& 16384 : aiCalc_log_rate_tail(14);
		32768 &&& 32768 : aiCalc_log_rate_tail(15);
		65536 &&& 65536 : aiCalc_log_rate_tail(16);
		131072 &&& 131072 : aiCalc_log_rate_tail(17);
		262144 &&& 262144 : aiCalc_log_rate_tail(18);
		524288 &&& 524288 : aiCalc_log_rate_tail(19);
		1048576 &&& 1048576 : aiCalc_log_rate_tail(20);
		2097152 &&& 2097152 : aiCalc_log_rate_tail(21);
		4194304 &&& 4194304 : aiCalc_log_rate_tail(22);
		8388608 &&& 8388608 : aiCalc_log_rate_tail(23);
		16777216 &&& 16777216 : aiCalc_log_rate_tail(24);
		33554432 &&& 33554432 : aiCalc_log_rate_tail(25);
		67108864 &&& 67108864 : aiCalc_log_rate_tail(26);
		134217728 &&& 134217728 : aiCalc_log_rate_tail(27);
		268435456 &&& 268435456 : aiCalc_log_rate_tail(28);
		536870912 &&& 536870912 : aiCalc_log_rate_tail(29);
		1073741824 &&& 1073741824 : aiCalc_log_rate_tail(30);
		2147483648 &&& 2147483648 : aiCalc_log_rate_tail(31);
		_ : aiCalc_log_rate_tail(0);
	}
}