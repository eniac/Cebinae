action aiCalc_log_relative_round_m_dt(bit<8> log_v) {log_relative_round_m_dt = log_v;}
table tiCalc_log_relative_round_m_dt {
    key = { relative_round_m_dt : ternary; }
    actions = { aiCalc_log_relative_round_m_dt; }
	const entries = {
		1 &&& 1 : aiCalc_log_relative_round_m_dt(0);
		2 &&& 2 : aiCalc_log_relative_round_m_dt(1);
		4 &&& 4 : aiCalc_log_relative_round_m_dt(2);
		8 &&& 8 : aiCalc_log_relative_round_m_dt(3);
		16 &&& 16 : aiCalc_log_relative_round_m_dt(4);
		32 &&& 32 : aiCalc_log_relative_round_m_dt(5);
		64 &&& 64 : aiCalc_log_relative_round_m_dt(6);
		128 &&& 128 : aiCalc_log_relative_round_m_dt(7);
		256 &&& 256 : aiCalc_log_relative_round_m_dt(8);
		512 &&& 512 : aiCalc_log_relative_round_m_dt(9);
		1024 &&& 1024 : aiCalc_log_relative_round_m_dt(10);
		2048 &&& 2048 : aiCalc_log_relative_round_m_dt(11);
		4096 &&& 4096 : aiCalc_log_relative_round_m_dt(12);
		8192 &&& 8192 : aiCalc_log_relative_round_m_dt(13);
		16384 &&& 16384 : aiCalc_log_relative_round_m_dt(14);
		32768 &&& 32768 : aiCalc_log_relative_round_m_dt(15);
		65536 &&& 65536 : aiCalc_log_relative_round_m_dt(16);
		131072 &&& 131072 : aiCalc_log_relative_round_m_dt(17);
		262144 &&& 262144 : aiCalc_log_relative_round_m_dt(18);
		524288 &&& 524288 : aiCalc_log_relative_round_m_dt(19);
		1048576 &&& 1048576 : aiCalc_log_relative_round_m_dt(20);
		2097152 &&& 2097152 : aiCalc_log_relative_round_m_dt(21);
		4194304 &&& 4194304 : aiCalc_log_relative_round_m_dt(22);
		8388608 &&& 8388608 : aiCalc_log_relative_round_m_dt(23);
		16777216 &&& 16777216 : aiCalc_log_relative_round_m_dt(24);
		33554432 &&& 33554432 : aiCalc_log_relative_round_m_dt(25);
		67108864 &&& 67108864 : aiCalc_log_relative_round_m_dt(26);
		134217728 &&& 134217728 : aiCalc_log_relative_round_m_dt(27);
		268435456 &&& 268435456 : aiCalc_log_relative_round_m_dt(28);
		536870912 &&& 536870912 : aiCalc_log_relative_round_m_dt(29);
		1073741824 &&& 1073741824 : aiCalc_log_relative_round_m_dt(30);
		2147483648 &&& 2147483648 : aiCalc_log_relative_round_m_dt(31);
		_ : aiCalc_log_relative_round_m_dt(0);
	}
}