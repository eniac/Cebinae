double as_gbps(double byte_ct, double elapsed_s) {
    double GB_ct = byte_ct / 1000000000.0;
    double Gb_ct = GB_ct * 8;
    double Gbps = Gb_ct / elapsed_s;
    if (byte_ct == 0) {
        return 0;
    }
    else {
        return Gbps;
    }
}

void print_debug_start(int intervalCt, 
    int last_headq, int headq, 
    uint8_t last_high_prio_queue, uint8_t cur_high_prio_queue,
    uint32_t port_byte_ct, double elapsed_s,
    uint32_t port_byte_thresh
    ) {
    cout << "--------------------" << endl;
    cout << "interval: "<< intervalCt << endl;
    cout << "headq: " << last_headq << " --> " << headq << endl;
    cout << "high priority queue id " << (uint32_t)last_high_prio_queue << " --> " << (uint32_t)cur_high_prio_queue << endl;
    cout << "bottleneck port byte ct: " << port_byte_ct << "B in " << elapsed_s << "s " 
    << "("<< fixed << as_gbps(port_byte_ct, elapsed_s) << "Gb/s)" << endl;
    cout << "bottleneck port byte THRESH: " << port_byte_thresh << "B" << endl;

}

void ipaddr_to_string(uint32_t iaddr, char * saddr) {
    const int NBYTES = 4;
    uint8_t octet[NBYTES];
    for(int i = 0 ; i < NBYTES ; i++)
    {
        octet[i] = iaddr >> (i * 8);
    }
    sprintf(saddr, "%d.%d.%d.%d", octet[3], octet[2], octet[1], octet[0]);
    return;
}

void print_flow(uint32_t src, uint32_t dst, uint32_t byte_ct, double elapsed_s) {
    char src_str[16];
    char dst_str[16];
    ipaddr_to_string(src, src_str);
    ipaddr_to_string(dst, dst_str);
    double gbps = as_gbps(byte_ct, elapsed_s);
    cout << src_str << " --> " << dst_str << " : " << byte_ct << " B -- " << gbps << " Gb/s " << endl;
}


void print_debug_rates(uint32_t top_bytes, 
        uint32_t bot_bytes, 
        uint32_t last_top_size, 
        uint32_t last_bot_size
    ) {
    cout << "top size: " << top_bytes << endl;
    cout << "bot size: " << bot_bytes << endl;
    cout << "last top size: " << last_top_size << endl;
    cout << "last bot size: " << last_bot_size << endl;
}

void print_debug_queuects(uint32_t to_head, uint32_t to_tail, uint32_t to_drop) {
    cout << "---- packet queue decisions ----" << endl;
    cout << "to_head: " << to_head << endl;
    cout << "to_tail: " << to_tail << endl;
    cout << "to_drop: " << to_drop << endl;
}

typedef p4_pd_status_t (*single_idx_reader)(p4_pd_sess_hdl_t, p4_pd_dev_target_t, int, int, uint32_t*, int*); 

uint32_t poll_by_function(single_idx_reader reader, uint32_t idx) {
    int flags = REGISTER_READ_HW_SYNC; // sync with hw
    uint32_t regvals[NUM_PIPES];
    int valct = 0;
    p4_pd_status_t pd_status = reader(pd_sess_hdl, pd_dev_tgt_tables, idx, flags, regvals, &valct);
    if (pd_status != 0) {
        cout << "[pollHere] pd_status error." << endl;
    }
    return regvals[TEST_PIPE];

}
uint32_t pollfCount(int idx) {
    return poll_by_function(
        p4_pd_main_register_read_Ingress_t_igr_fCount,
        idx
    );
}
uint32_t pollbytes(int idx) {
    return poll_by_function(
        p4_pd_main_register_read_Ingress_t_igr_riBytes,
        idx
    );
}

uint32_t pollrotate_last_sizebytes(int idx) {
    return poll_by_function(
        p4_pd_main_register_read_Ingress_t_igr_riRotateLastSize,
        idx
    );
}



void print_debug_registers() {
    // cout << "here[128] = " << pollHere(128) << endl;
    // cout << "here[256] = " << pollHere(256) << endl;
    cout << "----- debug registers -----" << endl;
    cout << "packets classified as top: " << pollfCount(0) << endl;
    cout << "packets classified as bottom: " << pollfCount(1) << endl;
    cout << "bytes top: " << pollbytes(256) << endl;
    cout << "bytes bottom: " << pollbytes(128) << endl;
    cout << "last bytes subtracted from top: " << pollrotate_last_sizebytes(256) << endl;
    cout << "last bytes subtracted from bottom: " << pollrotate_last_sizebytes(128) << endl;
}



