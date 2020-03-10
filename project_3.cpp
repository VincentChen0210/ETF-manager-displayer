#include <iostream>
#include "project3.hpp"
#include "History_Transaction_definitions.hpp"

#ifndef MARMOSET_TESTING

unsigned int Transaction::assigned_trans_id = 0;

int main() {
	 History trans_history{};
	 trans_history.read_history();

	 std::cout << "[Starting history]:" << std::endl;
	 std::cout << "========== BEGIN TRANSACTION HISTORY ========" << std::endl;
	 std::cout << "  ID SYMB   DD   MM  YYYY   TYPE  SHRS     AMOUNT        ACB  SHR BAL  ACB P SHR        CGL" << std::endl;
	 std::cout << std::endl;
	 trans_history.print();
	 std::cout << "========== END TRANSACTION HISTORY ========" << std::endl;

	 trans_history.sort_by_date();

	 std::cout << "[Sorted ]:" << std::endl;
	 std::cout << "========== BEGIN TRANSACTION HISTORY ========" << std::endl;
	 std::cout << "  ID SYMB   DD   MM  YYYY   TYPE  SHRS     AMOUNT        ACB  SHR BAL  ACB P SHR        CGL" << std::endl;
	 std::cout << std::endl;
	 trans_history.print();
	 std::cout << "========== END TRANSACTION HISTORY ========" << std::endl;

	 trans_history.update_acb_cgl();

	 std::cout << "========== BEGIN TRANSACTION HISTORY ========" << std::endl;
	 std::cout << "  ID SYMB   DD   MM  YYYY   TYPE  SHRS     AMOUNT        ACB  SHR BAL  ACB P SHR        CGL" << std::endl;
	 std::cout << std::endl;
	 trans_history.print();
	 std::cout << "========== END TRANSACTION HISTORY ========" << std::endl;

	 std::cout << "[CGL for 2018 ]: " << trans_history.compute_cgl(2018) << std::endl;
	 std::cout << "[CGL for 2019 ]: " << trans_history.compute_cgl(2019) << std::endl;

	 return 0;
}
#endif
