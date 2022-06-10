action aiCalc_log_relative_round(bit<8> log_v) {log_relative_round = log_v;}
table tiCalc_log_relative_round {
    key = { relative_round : ternary; }
    actions = { aiCalc_log_relative_round; }
	const entries = {
		1 &&& 1 : aiCalc_log_relative_round(0);
		2 &&& 2 : aiCalc_log_relative_round(1);
		4 &&& 4 : aiCalc_log_relative_round(2);
		8 &&& 8 : aiCalc_log_relative_round(3);
		16 &&& 16 : aiCalc_log_relative_round(4);
		32 &&& 32 : aiCalc_log_relative_round(5);
		64 &&& 64 : aiCalc_log_relative_round(6);
		128 &&& 128 : aiCalc_log_relative_round(7);
		256 &&& 256 : aiCalc_log_relative_round(8);
		512 &&& 512 : aiCalc_log_relative_round(9);
		1024 &&& 1024 : aiCalc_log_relative_round(10);
		2048 &&& 2048 : aiCalc_log_relative_round(11);
		4096 &&& 4096 : aiCalc_log_relative_round(12);
		8192 &&& 8192 : aiCalc_log_relative_round(13);
		16384 &&& 16384 : aiCalc_log_relative_round(14);
		32768 &&& 32768 : aiCalc_log_relative_round(15);
		65536 &&& 65536 : aiCalc_log_relative_round(16);
		131072 &&& 131072 : aiCalc_log_relative_round(17);
		262144 &&& 262144 : aiCalc_log_relative_round(18);
		524288 &&& 524288 : aiCalc_log_relative_round(19);
		1048576 &&& 1048576 : aiCalc_log_relative_round(20);
		2097152 &&& 2097152 : aiCalc_log_relative_round(21);
		4194304 &&& 4194304 : aiCalc_log_relative_round(22);
		8388608 &&& 8388608 : aiCalc_log_relative_round(23);
		16777216 &&& 16777216 : aiCalc_log_relative_round(24);
		33554432 &&& 33554432 : aiCalc_log_relative_round(25);
		67108864 &&& 67108864 : aiCalc_log_relative_round(26);
		134217728 &&& 134217728 : aiCalc_log_relative_round(27);
		268435456 &&& 268435456 : aiCalc_log_relative_round(28);
		536870912 &&& 536870912 : aiCalc_log_relative_round(29);
		1073741824 &&& 1073741824 : aiCalc_log_relative_round(30);
		2147483648 &&& 2147483648 : aiCalc_log_relative_round(31);
		_ : aiCalc_log_relative_round(0);
	}
}