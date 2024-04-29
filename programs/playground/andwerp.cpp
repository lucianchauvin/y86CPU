#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool error = false;
void log_error(string s) {
    cout << "ERROR " << s << endl;
    error = true;
}

vector<string> split(string s) {
    set<char> split_chars;
    split_chars.insert(' ');
    split_chars.insert(',');
    split_chars.insert('(');
    split_chars.insert(')');
    split_chars.insert('$');
    split_chars.insert('\t');
    vector<string> ret(0);
    int ptr = 0;
    while(ptr != s.size()) {
        while(ptr != s.size() && split_chars.count(s[ptr])){
            ptr ++;
        }
        if(ptr == s.size()) {
            break;
        }
        string cur = "";
        while(ptr != s.size() && !split_chars.count(s[ptr])){
            cur.push_back(s[ptr ++]);
        }
        ret.push_back(cur);
    }
    return ret;
}

vector<string> register_names = {"%rax", "%rcx", "%rdx", "%rbx", "%rsp", "%rbp", "%rsi", "%rdi", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14"};
int register_to_int(string s) {
    for(int i = 0; i < 15; i++){
        if(s == register_names[i]) {
            return i;
        }
    }
    log_error("invalid register name : " + s);
    return 15;
}

//big endian order
void pb_ll_hex(vector<int>& arr, ll val) {
    for(int i = 0; i < 16; i++){
        arr.push_back((val >> ((15 - i) * 4)) & 0xf);
    }
}

map<string, int> f_id;  //maps function names to function id
map<int, string> rf_id; //maps function id to function names
map<string, ll> f_map; //maps function names to byte addresses
int get_fn_id(string name) {
    if(!f_id.count(name)) {
        f_id[name] = f_id.size();
        rf_id[f_id[name]] = name;
    }
    return f_id[name];
}

char int_to_hex(int val) {
    if(val < 0 || val > 15) {
        log_error("invalid hex value : " + to_string(val));
        return 0;
    }
    if(val <= 9) {
        return '0' + val;
    }
    else {
        return 'a' + val;
    }
}

int main(int argc, char* argv[]) {
    vector<string> args(0);
    for(int i = 0; i < argc; i++){
        string cur = "";
        for(int j = 0; argv[i][j] != '\0'; j++) {
            cur.push_back(argv[i][j]);
        }
        args.push_back(cur);
    }

    string r_addr = args[1];
    string w_addr = args[2];
    ifstream fin; fin.open(r_addr);
    ofstream fout; fout.open(w_addr);

    //first pass to gather instruction data and get function positions
    vector<vector<int>> instr_list(0);
    int byte_ptr = 0;
    while(true) {
        string line;
        getline(fin, line);
        if(fin.eof()) {
            break;
        }
        vector<string> token = split(line);
        if(token.size() == 0){
            continue;
        }
        if(token[0][token[0].size() - 1] == ':' || (token.size() >= 2 && token[1][0] == ':')) {
            //function
            string f_name;
            if(token[0][token[0].size() - 1] == ':') {
                f_name = token[0].substr(0, token[0].size() - 1);
            }
            else {
                f_name = token[0];
            }
            f_map[f_name] = byte_ptr;
            continue;
        }
        //some sort of instruction
        vector<int> cur_instr(0);
        int icode, ifun;
        if(token[0] == "halt") {
            icode = 0;
            ifun = 0;
            cur_instr = {icode, ifun};
            byte_ptr ++;
        }
        else if(token[0] == "nop") {
            icode = 1;
            ifun = 0;
            cur_instr = {icode, ifun};
            byte_ptr ++;
        }
        else if(token[0] == "rrmovq" || token[0] == "cmovle" || token[0] == "cmovl" || token[0] == "cmove" || token[0] == "cmovne" || token[0] == "cmovge" || token[0] == "cmovg") {
            icode = 2;
            if(token[0] == "rrmovq") {
                ifun = 0;
            }
            else if(token[0] == "cmovle") {
                ifun = 1;
            }
            else if(token[0] == "cmovl") {
                ifun = 2;
            }
            else if(token[0] == "cmove") {
                ifun = 3;
            }
            else if(token[0] == "cmovne") {
                ifun = 4;
            }
            else if(token[0] == "cmovge") {
                ifun = 5;
            }
            else if(token[0] == "cmovg") {
                ifun = 6;
            }
            int rA = register_to_int(token[1]);
            int rB = register_to_int(token[2]);
            cur_instr = {icode, ifun, rA, rB};
            byte_ptr += 2;
        }
        else if(token[0] == "irmovq") {
            icode = 3;
            ifun = 0;
            int rA = 15;
            int rB = register_to_int(token[2]);
            ll val = stoll(token[1]);
            cur_instr = {icode, ifun, rA, rB};
            pb_ll_hex(cur_instr, val);
            byte_ptr += 10;
        }
        else if(token[0] == "rmmovq") {
            icode = 4;
            ifun = 0;
            int rA = register_to_int(token[1]);
            int rB = register_to_int(token[3]);
            ll val = stoll(token[2]);
            cur_instr = {icode, ifun, rA, rB};
            pb_ll_hex(cur_instr, val);
            byte_ptr += 10;
        }
        else if(token[0] == "mrmovq") {
            icode = 5;
            ifun = 0;
            int rA = register_to_int(token[3]);
            int rB = register_to_int(token[2]);
            ll val = stoll(token[1]);
            cur_instr = {icode, ifun, rA, rB};
            pb_ll_hex(cur_instr, val);
            byte_ptr += 10;
        }
        else if(token[0] == "addq" || token[0] == "subq" || token[0] == "andq" || token[0] == "xorq" || token[0] == "mulq" || token[0] == "divq" || token[0] == "modq") {
            icode = 6;
            if(token[0] == "addq") {
                ifun = 0;
            }
            else if(token[0] == "subq") {
                ifun = 1;
            }
            else if(token[0] == "andq") {
                ifun = 2;
            }
            else if(token[0] == "xorq") {
                ifun = 3;
            }
            else if(token[0] == "mulq") {
                ifun = 4;   
            }
            else if(token[0] == "divq") {
                ifun = 5;
            }
            else if(token[0] == "modq") {
                ifun = 6;
            }
            int rA = register_to_int(token[1]);
            int rB = register_to_int(token[2]);
            cur_instr = {icode, ifun, rA, rB};
            byte_ptr += 2;
        }
        else if(token[0] == "jmp" || token[0] == "jle" || token[0] == "jl" || token[0] == "je" || token[0] == "jne" || token[0] == "jge" || token[0] == "jg") {
            icode = 7;
            if(token[0] == "jmp") {
                ifun = 0;
            }
            else if(token[0] == "jle") {
                ifun = 1;
            }
            else if(token[0] == "jl") {
                ifun = 2;
            }
            else if(token[0] == "je") {
                ifun = 3;
            }
            else if(token[0] == "jne") {
                ifun = 4;
            }
            else if(token[0] == "jge") {
                ifun = 5;
            }
            else if(token[0] == "jg") {
                ifun = 6;
            }
            string dest = token[1];
            cur_instr = {icode, ifun, get_fn_id(dest)};
            byte_ptr += 9;
        }
        else if(token[0] == "call") {
            icode = 8;
            ifun = 0;
            string dest = token[1];
            cur_instr = {icode, ifun, get_fn_id(dest)};
            byte_ptr += 9;
        }
        else if(token[0] == "ret") {
            icode = 9;
            ifun = 0;
            cur_instr = {icode, ifun};
            byte_ptr += 1;
        }
        else if(token[0] == "pushq") {
            icode = 10;
            ifun = 0;
            int rA = register_to_int(token[1]);
            int rB = 15;
            cur_instr = {icode, ifun, rA, rB};
            byte_ptr += 2;
        }
        else if(token[0] == "popq") {
            icode = 11;
            ifun = 0;
            int rA = register_to_int(token[1]);
            int rB = 15;
            cur_instr = {icode, ifun, rA, rB};
            byte_ptr += 2;
        }
        else {
            log_error("invalid instruction name : " + token[0]);
        }
        instr_list.push_back(cur_instr);
    }

    //second pass, go through instruction list with knowledge of function locations
    vector<int> hex_arr(0);
    for(int i = 0; i < instr_list.size(); i++){
        int icode = instr_list[i][0];
        if(icode == 7 || icode == 8) {
            //turn function id into byte address
            string f_name = rf_id[instr_list[i][2]];
            if(!f_map.count(f_name)) {
                log_error("function name does not exist : " + f_name);
                continue;
            }
            ll addr = f_map[f_name];
            instr_list[i].pop_back();
            pb_ll_hex(instr_list[i], addr);
        }
        
        //push all hex onto hex_arr
        for(int j = 0; j < instr_list[i].size(); j++){
            hex_arr.push_back(instr_list[i][j]);
        }
    }
    

    //pad hex out to rom size
    ll addr_bits = 12;
    ll rom_size = (1ll << addr_bits);
    if(hex_arr.size() > rom_size * 2) {
        log_error("program exceeds size of ROM : " + to_string(hex_arr.size()));
    }
    while(hex_arr.size() < rom_size * 2){
        hex_arr.push_back(0);
    }

    //print to output file
    fout << "v3.0 hex words addressed" << "\n";
    for(int i = 0; i < hex_arr.size(); i += 32) {
        fout << hex << setfill('0') << setw(addr_bits / 4) << (i / 2) << ":";
        for(int j = 0; j < 16; j++){
            fout << " " << hex << hex_arr[i + j * 2 + 0] << hex_arr[i + j * 2 + 1];
        }
        fout << "\n";
    }

    if(error){
        cout << "build finished with error(s)" << endl;
    }

    fin.close(); fout.close();

    return 0;
}