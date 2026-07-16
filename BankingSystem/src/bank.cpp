#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../include/BankVault.h"

// 
// @students, your code must have:
//   TransactionList: deposit(), withdraw(), transfer(), length(),
//                    collapse(), sort(), operator+=, operator<<
//   BankVault:       applyTransactions()
// 

struct TestResult { std::string name; bool passed; };
std::vector<TestResult> results;

void check(const std::string& name, bool passed) {
    results.push_back({name, passed});
    std::cout << "  " << (passed ? "[PASS]" : "[FAIL]") << " " << name << "\n";
}


std::string dump(const TransactionList& tl) {
    std::ostringstream oss;
    oss << tl;
    return oss.str();
}

int lineCount(const TransactionList& tl) {
    std::string s = dump(tl);
    if (s.empty()) return 0;
    return (int)std::count(s.begin(), s.end(), '\n');
}

bool contains(const TransactionList& tl, const std::string& sub) {
    return dump(tl).find(sub) != std::string::npos;
}

bool verifyAccountOrder(const TransactionList& tl) {
    std::istringstream iss(dump(tl));
    std::string line; unsigned int prev = 0;
    while (std::getline(iss, line)) {
        if (line.empty()) continue;
        std::istringstream ls(line); std::string tok; int idx = 0;
        unsigned int acct = 0;
        while (ls >> tok) { 
            if (idx == 2) { 
                acct = (unsigned int)std::stoul(tok); 
                break; 
            } 
            ++idx; 
        }
        if (acct < prev) return false;
        prev = acct;
    }
    return true;
}

bool verifyDollarsOrder(const TransactionList& tl) {
    std::istringstream iss(dump(tl));
    std::string line; int prev = 0;
    while (std::getline(iss, line)) {
        if (line.empty()) continue;
        std::istringstream ls(line); std::string tok; int idx = 0; int dollars = 0;
        while (ls >> tok) { 
            if (idx == 1) { 
                dollars = std::stoi(tok.substr(1)); 
                break; 
            } 
            ++idx; 
        }
        if (dollars < prev) return false;
        prev = dollars;
    }
    return true;
}

bool verifyTypeOrder(const TransactionList& tl) {
    std::istringstream iss(dump(tl));
    std::string line, prev = "";
    while (std::getline(iss, line)) {
        if (line.empty()) continue;
        std::string label = line.substr(0, line.find(' '));
        if (!prev.empty() && label < prev) return false;
        prev = label;
    }
    return true;
}

int main() {

    std::cout << "===========================================\n";
    std::cout << "         CP3 DRIVER — bank.cpp             \n";
    std::cout << "===========================================\n\n";

    // 
    // 1. deposit / withdraw / transfer / length
    // 
    std::cout << " 1. deposit / withdraw / transfer / length\n";

    TransactionList list;
    check("1a empty list length = 0", list.length() == 0);

    list.deposit (500, 1001);
    check("1b length after deposit = 1",  list.length() == 1);
    check("1b deposit appears in output", contains(list, "1001"));

    list.withdraw(300, 2002);
    check("1c length after withdraw = 2",  list.length() == 2);
    check("1c withdraw appears in output", contains(list, "2002"));

    list.transfer(100, 1001, 2002);
    check("1d length after transfer = 3",  list.length() == 3);
    check("1d transfer appears in output", contains(list, "1001") && contains(list, "2002"));

    std::cout << list << "\n";

    // 
    // 2. Display — operator<<
    //    Format: <type> $<amount> <account> {<to_acct>}
    // 
    std::cout << " 2. Display (operator<<) \n";

    TransactionList venmo;
    venmo.deposit (400, 1234);
    venmo.withdraw(200, 4321);
    venmo.deposit (805, 1234);
    venmo.transfer(100, 1234, 4321);

    std::string venmoStr = dump(venmo);
    check("2a output is non-empty",!venmoStr.empty());
    check("2b 4 lines for 4 nodes",lineCount(venmo) == 4);
    check("2c deposit $400 present",venmoStr.find("400")  != std::string::npos);
    check("2d withdraw $200 present",venmoStr.find("200")  != std::string::npos);
    check("2e transfer shows both accts",venmoStr.find("1234") != std::string::npos && venmoStr.find("4321") != std::string::npos);
    check("2f dollar sign in output",venmoStr.find("$") != std::string::npos);
    std::cout << "Venmo transactions:\n" << venmo << "\n";

    // 
    // 3. COLLAPSE
    // 
    std::cout << " 3. collapse \n";

    // 3a: basic net — deposit $500, withdraw $300, deposit $200 -> Deposit $400
    TransactionList c1;
    c1.deposit (500, 1001);
    c1.withdraw(300, 1001);
    c1.deposit (200, 1001);
    std::cout << "[3a] Before:\n" << c1;
    int n = c1.collapse();
    std::string c1str = dump(c1);
    check("3a returns 1 distinct account",  n == 1);
    check("3a collapses to 1 node", lineCount(c1) == 1);
    check("3a net is Deposit", c1str.find("Deposit") != std::string::npos);
    check("3a net amount is $400", c1str.find("400") != std::string::npos);
    std::cout << "[3a] After:\n" << c1 << "\n";

    // 3b: transfer exploded — no Transfer nodes remain
    TransactionList c2;
    c2.deposit (500, 1001);
    c2.transfer(100, 1001, 2002);
    c2.withdraw(200, 2002);
    std::cout << "[3b] Before:\n" << c2;
    n = c2.collapse();
    std::string c2str = dump(c2);
    check("3b returns 2 distinct accounts",n == 2);
    check("3b no Transfer nodes remain", c2str.find("Transfer") == std::string::npos);
    check("3b 1001 net is Deposit $400", c2str.find("400") != std::string::npos);
    check("3b 2002 net is Withdraw $100", c2str.find("100") != std::string::npos);
    std::cout << "[3b] After:\n" << c2 << "\n";

    // 3c: net negative -> Withdraw
    TransactionList c3;
    c3.deposit (100, 1001);
    c3.withdraw(400, 1001);
    std::cout << "[3c] Before:\n" << c3;
    n = c3.collapse();
    std::string c3str = dump(c3);
    check("3c returns 1 distinct account", n == 1);
    check("3c net negative is Withdraw", c3str.find("Withdraw") != std::string::npos);
    check("3c net amount is $300", c3str.find("300") != std::string::npos);
    std::cout << "[3c] After:\n" << c3 << "\n";

    // 3d: multiple accounts
    TransactionList c4;
    c4.deposit (500, 1001);
    c4.deposit (300, 2002);
    c4.withdraw(200, 1001);
    c4.deposit (100, 3003);
    c4.withdraw(100, 2002);
    n = c4.collapse();
    check("3d returns 3 distinct accounts",  n == 3);
    check("3d collapses to 3 nodes",         lineCount(c4) == 3);
    std::cout << "[3d] Multi-account collapse:\n" << c4 << "\n";

    // 
    // 4. SORT
    // 
    std::cout << " 4. sort \n";

    // 4a: by account_number — 8 nodes reverse order (worst case)
    TransactionList s1;
    s1.deposit(100, 8001);
    s1.deposit(100, 7001);
    s1.deposit(100, 6001);
    s1.deposit(100, 5001);
    s1.deposit(100, 4001);
    s1.deposit(100, 3001);
    s1.deposit(100, 2001);
    s1.deposit(100, 1001);
    std::cout << "[4a] Before (8 nodes reverse by account_number):\n" << s1;
    int swaps = s1.sort("account_number");
    std::cout << "[4a] After (" << swaps << " swaps):\n" << s1;
    check("4a account_number order correct", verifyAccountOrder(s1));
    check("4a account_number unsorted count > 0", swaps > 0);
    check("4a account_number already sorted = 0", s1.sort("account_number") == 0);
    std::cout << "\n";

    // 4b: by dollars — 8 nodes reverse order (worst case)
    TransactionList s2;
    s2.deposit(800, 1001);
    s2.deposit(700, 1001);
    s2.deposit(600, 1001);
    s2.deposit(500, 1001);
    s2.deposit(400, 1001);
    s2.deposit(300, 1001);
    s2.deposit(200, 1001);
    s2.deposit(100, 1001);
    std::cout << "[4b] Before (8 nodes reverse by dollars):\n" << s2;
    swaps = s2.sort("dollars");
    std::cout << "[4b] After (" << swaps << " swaps):\n" << s2;
    check("4b dollars order correct", verifyDollarsOrder(s2));
    check("4b dollars unsorted count > 0", swaps > 0);
    check("4b dollars already sorted = 0", s2.sort("dollars") == 0);
    std::cout << "\n";

    // 4c: by transaction_type — 6 nodes fully reverse (W W T T D D)
    // Alphabetical sorted order: D D T T W W
    TransactionList s3;
    s3.withdraw(100, 1001);
    s3.transfer(200, 4004, 5005);
    s3.withdraw(200, 2002);
    s3.deposit (100, 5005);
    s3.transfer(100, 3003, 4004);   
    s3.deposit (200, 6006);
    std::cout << "[4c] Before (6 nodes reverse by transaction_type):\n" << s3;
    swaps = s3.sort("transaction_type");
    std::cout << "[4c] After (" << swaps << " swaps):\n" << s3;
    check("4c transaction_type order correct", verifyTypeOrder(s3));
    check("4c transaction_type unsorted count > 0", swaps > 0);
    check("4c transaction_type already sorted = 0", s3.sort("transaction_type") == 0);
    std::cout << "\n";

    // 4d: invalid key -> -1, list unchanged
    TransactionList s4;
    s4.deposit(100, 1001);
    s4.deposit(200, 2002);
    swaps = s4.sort("invalid_key");
    check("4d invalid key returns -1", swaps == -1);
    check("4d invalid key list unchanged", lineCount(s4) == 2);
    std::cout << "\n";

    // 
    // 5. OPERATOR +=
    // 
    std::cout << " 5. operator+= \n";

    // 5a: normal merge
    TransactionList m1, m2;
    m1.deposit(100, 1001);
    m1.deposit(200, 2002);
    m2.deposit(300, 3003);
    m2.deposit(400, 4004);
    std::cout << "[5a] list1 before:\n" << m1;
    std::cout << "[5a] list2 before:\n" << m2;
    m1 += m2;
    check("5a merged length = 4", m1.length() == 4);
    check("5a other is empty", m2.length() == 0);
    check("5a all nodes present", contains(m1, "1001") && contains(m1, "4004"));
    std::cout << "[5a] After merge:\n" << m1 << "\n";

    // 5b: self-merge — list unchanged
    TransactionList m3;
    m3.deposit(100, 1001);
    m3.deposit(200, 2002);
    m3 += m3;
    check("5b self-merge length unchanged", m3.length() == 2);
    check("5b self-merge content intact", contains(m3, "1001") && contains(m3, "2002"));
    std::cout << "\n";

    // 
    // 6. RULE OF THREE
    // 
    std::cout << " 6. Rule of Three \n";

    TransactionList original;
    original.deposit(999, 1001);
    original.withdraw(111, 2002);

    // 6a: copy constructor — deep copy
    TransactionList byCtor(original);
    original.deposit(1, 3003); // mutate original
    check("6a copy ctor: copy length = 2", byCtor.length()   == 2);
    check("6a copy ctor: original length = 3", original.length() == 3);
    check("6a copy ctor: copy has 1001", contains(byCtor, "1001"));
    check("6a copy ctor: copy does not have 3003", !contains(byCtor, "3003"));
    std::cout << "[6a] Original (3 nodes):\n" << original;
    std::cout << "[6a] Copy via ctor (2 nodes):\n" << byCtor << "\n";

    // 6b: copy assignment — deep copy
    TransactionList byAssign;
    byAssign = original;
    original.deposit(2, 4004); // mutate again
    check("6b copy assign: copy length = 3", byAssign.length() == 3);
    check("6b copy assign: original length = 4", original.length() == 4);
    check("6b copy assign: copy does not have 4004",!contains(byAssign, "4004"));
    std::cout << "[6b] Original (4 nodes):\n" << original;
    std::cout << "[6b] Copy via assignment (3 nodes):\n" << byAssign << "\n";

    // 6c: self-assignment — safe, unchanged
    byAssign = byAssign;
    check("6c self-assignment safe, length = 3", byAssign.length() == 3);
    std::cout << "\n";

    // 
    // 7. BANKVAULT — applyTransactions
    // 
    std::cout << " 7. BankVault::applyTransactions \n";

    BankVault vault(4);
    Account a1("Alice", 2020, 1001, "Checking", 1000);
    Account a2("Bob", 2019, 2002, "Savings",   500);
    Account a3("Carol", 2021, 3003, "Checking", 2000);
    vault.addAccount(a1);
    vault.addAccount(a2);
    vault.addAccount(a3);

    std::cout << "[7] Initial vault:\n";
    vault.display(2026);
    std::cout << "\n";

    TransactionList txns;
    txns.deposit (200, 1001);        // valid -> applied
    txns.withdraw(100, 2002);        // valid -> applied
    txns.transfer(300, 3003, 1001);  // both valid -> applied
    txns.deposit ( 50, 9999);        // unknown -> stays
    txns.transfer(100, 1001, 8888);  // 8888 unknown -> stays

    std::cout << "[7] Transactions before apply:\n" << txns << "\n";
    bool ok = vault.applyTransactions(txns);
    check("7a returns true when applied", ok == true);
    check("7b 2 unapplied nodes remain", txns.length() == 2);
    check("7c unknown deposit stays in list", contains(txns, "9999"));
    check("7d partial transfer stays in list",contains(txns, "8888"));
    check("7e deposit applied: 1001 = $1500", vault.findAccount(1001).getBalance() == 1500);
    check("7f withdraw applied: 2002 = $400", vault.findAccount(2002).getBalance() == 400);
    check("7g transfer applied: 3003 = $1700",vault.findAccount(3003).getBalance() == 1700);
    std::cout << "[7] Vault after apply:\n";
    vault.display(2026);
    std::cout << "\n";

    // 7h: all unknown -> returns false
    TransactionList badTxns;
    badTxns.deposit(100, 9999);
    badTxns.deposit(200, 8888);
    ok = vault.applyTransactions(badTxns);
    check("7h all unknown returns false", ok == false);
    std::cout << "\n";

    // 
    // 8. Fake Account
    // 
    std::cout << " 8. Fake Account \n";

    int before = vault.findAccount(1001).getBalance();
    TransactionList hack;
    hack.deposit (1000000, 5555);        // fake account
    hack.transfer(1000000, 5555, 1001);  // transfer to real account
    hack.collapse();
    vault.applyTransactions(hack);
    check("8a fake account: 1001 balance increased by $1000000", vault.findAccount(1001).getBalance() == before + 1000000);
    std::cout << "\n";

    // 
    // 9. BIG LIST STRESS TEST
    // 
    std::cout << " 9. Big List Stress Test \n";

    BankVault bigVault(10);
    Account accts[10] = {
        Account("Alice", 2015,1, "Checking", 5000),
        Account("Bob",2016,2, "Savings",  3000),
        Account("Carol",2017,3, "Checking", 8000),
        Account("Dave",2018,4, "Savings",  1000),
        Account("Eve",2019,5, "Checking", 6000),
        Account("Frank",2020,6, "Savings",  2000),
        Account("Grace",2021,7, "Checking", 9000),
        Account("Hank",2022,8, "Savings",  4000),
        Account("Ivy",2023,9, "Checking", 7000),
        Account("Jack",2024,10, "Savings",   500)
    };
    for (int i = 0; i < 10; i++)
        bigVault.addAccount(accts[i]);

    // Build 50 transactions
    TransactionList big;
    for (int i = 0; i < 5; i++) {
        big.deposit (100*(i+1),1);
        big.deposit (200*(i+1),2);
        big.withdraw(150*(i+1),3);
        big.withdraw( 50*(i+1),4);
        big.transfer(300*(i+1),5,6);
        big.deposit (400*(i+1),7);
        big.withdraw(250*(i+1),8);
        big.transfer(100*(i+1),9,10);
        big.deposit ( 75*(i+1),3);
        big.withdraw( 25*(i+1),1);
    }
    check("9a big list length = 50", big.length() == 50);

    // 9b: sort by account_number
    TransactionList bigSorted = big;
    bigSorted.sort("account_number");
    check("9b sort account_number correct",verifyAccountOrder(bigSorted));
    check("9b sort account_number idempotent",   bigSorted.sort("account_number") == 0);

    // 9c: sort by dollars
    bigSorted = big;
    bigSorted.sort("dollars");
    check("9c sort dollars correct", verifyDollarsOrder(bigSorted));
    check("9c sort dollars idempotent",bigSorted.sort("dollars") == 0);

    // 9d: sort by transaction_type
    bigSorted = big;
    bigSorted.sort("transaction_type");
    check("9d sort transaction_type correct",verifyTypeOrder(bigSorted));
    check("9d sort transaction_type idempotent", bigSorted.sort("transaction_type") == 0);

    // 9e: collapse
    TransactionList bigCollapsed = big;
    int distinct = bigCollapsed.collapse();
    check("9e collapse 50 -> 10 accounts", distinct == 10);
    check("9e no Transfer nodes after collapse",
          dump(bigCollapsed).find("Transfer") == std::string::npos);

    // 9f: operator+= large lists
    TransactionList bigA, bigB;
    for (int i = 1; i <= 25; i++) { bigA.deposit(i*10, 1); bigB.deposit(i*10, 2); }
    bigA += bigB;
    check("9f merge: bigA length = 50", bigA.length() == 50);
    check("9f merge: bigB length = 0",  bigB.length() == 0);

    // 9g: apply collapsed to vault
    bigCollapsed.deposit(999, 9999);   // unknown
    bigCollapsed.deposit(999, 8888);   // unknown
    int beforeApply = bigCollapsed.length();
    bool bigOk = bigVault.applyTransactions(bigCollapsed);
    check("9g applyTransactions returns true",  bigOk == true);
    check("9g 2 unapplied remain", bigCollapsed.length() == 2);
    check("9g 10 applied", (beforeApply - (int)bigCollapsed.length()) == 10);
    check("9g acct 1 balance = 6125", bigVault.findAccount(1).getBalance()  == 6125);
    check("9g acct 7 balance = 15000",bigVault.findAccount(7).getBalance()  == 15000);

    // 9h: Rule of Three on big list
    TransactionList bigOrig;
    for (int i = 0; i < 20; i++)
        bigOrig.deposit(i * 100, (unsigned int)(i % 9 + 1));
    TransactionList bigCopy1(bigOrig);
    TransactionList bigCopy2; bigCopy2 = bigOrig;
    bigOrig.deposit(99999, 1);
    check("9h copy ctor independent (length = 20)", bigCopy1.length() == 20);
    check("9h copy assign independent (length = 20)", bigCopy2.length() == 20);
    check("9h original mutated (length = 21)",  bigOrig.length()  == 21);
    std::cout << "\n";

    // 
    // SUMMARY
    // 
    std::cout << "===========================================\n";
    std::cout << "               TEST SUMMARY                \n";
    std::cout << "===========================================\n";

    std::vector<std::string> failed;
    int passed = 0;
    for (const auto& r : results) {
        if (r.passed) ++passed;
        else failed.push_back(r.name);
    }
    int total = (int)results.size();
    std::cout << "Passed: " << passed << " / " << total << "\n";

    if (failed.empty()) {
        std::cout << "\n ALL TESTS PASSED\n";
    } else {
        std::cout << "\n FAILED TESTS (" << failed.size() << "):\n";
        for (const auto& name : failed)
            std::cout << "  - " << name << "\n";
    }
    std::cout << "===========================================\n";

    return failed.empty() ? 0 : 1;
}
