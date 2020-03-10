#ifndef _HISTORY_TRANSACTION_HPP_
#define _HISTORY_TRANSACTION_HPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project3.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK
//

Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,
        unsigned int month_date,  unsigned year_date,
        bool buy_sell_trans,  unsigned int number_shares,
        double trans_amount ){
	symbol = ticker_symbol;
	day = day_date;
	month = month_date;
	year = year_date;

	if (buy_sell_trans) {
		trans_type = "Buy";
	} else {
		trans_type = "Sell";
	}

	shares = number_shares;
	amount = trans_amount;

	p_next = nullptr;
	acb = 0;
	acb_per_share = 0;
	share_balance = 0;
	cgl = 0;
	trans_id = assigned_trans_id;
	assigned_trans_id++;
}

// Destructor
// TASK
//

Transaction::~Transaction() {

}
// TASK
// Overloaded < operator.
//

bool Transaction::operator<(Transaction const &other) {
	unsigned int sum_1{0}, sum_2{0};

	sum_1 = day + 50 * month + 1000 * year;
	sum_2 = other.get_day() + 50 * other.get_month() + 1000 * other.get_year();

	//std::cout << sum_1 << " " << sum_2 << std::endl;
	if (sum_1 < sum_2) {
		return true;
	} else {
		return false;
	}
}

// GIVEN
// Member functions to get values. 
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values. 
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " " 
    << std::setw(4) << get_symbol() << " " 
    << std::setw(4) << get_day() << " "  
    << std::setw(4) << get_month() << "  "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) { 
    std::cout << "  Buy   ";
  } else { std::cout << "  Sell  "; }

  std::cout << std::setw(4) << get_shares() << " " 
    << std::setw(10) << get_amount() << " " 
    << std::setw(10) << get_acb() << "     " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl() 
    << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK
//

History::History():
	p_head{nullptr} {
}

// Destructor
// TASK
//

History::~History() {
	while (p_head != nullptr) {
		Transaction *p_currenth{p_head};
		p_head = p_head->get_next();
		delete p_currenth;
		p_currenth = nullptr;
	}

	delete p_head;
	p_head = nullptr;
}

// TASK
// read_transaction(...): Read the transaction history from file. 
//

void History::read_history() {
	Transaction * current{nullptr};

	ece150::open_file();
	while (ece150::next_trans_entry()) {
		current = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(),ece150::get_trans_month(),ece150::get_trans_year(),ece150::get_trans_type(),ece150::get_trans_shares(),ece150::get_trans_amount());
		insert(current);
	}
	ece150::close_file();
}

// insert(...): Insert transaction into linked list.
//

void History::insert( Transaction *p_new_trans ) {
	Transaction *temp{p_head};

	if (temp == nullptr) {
		p_head = p_new_trans;
		p_new_trans->set_next(nullptr);
	} else {
		while (temp->get_next() != nullptr) {
			temp = temp->get_next();
		}

		temp->set_next(p_new_trans);
		p_new_trans->set_next(nullptr);
	}
}

// TASK
// sort_by_date(): Sort the linked list by trade date.
//

void History::sort_by_date() {
	std::size_t count{0};
	Transaction *p_hsorted{nullptr};
	Transaction *p_csorted{nullptr};
	Transaction *p_bsorted{nullptr};
	Transaction *temp{p_head};

	std::size_t ncount{0};

	for (Transaction *p_current_node{p_head}; p_current_node != nullptr; p_current_node = p_current_node->get_next()) {
		count++;
	}

	for (std::size_t i{0}; i < count; ++i){
		Transaction *p_current{temp};
		temp = temp->get_next();
		Transaction *test{p_hsorted};
		//There are no nodes, assign p_current to head
		if (p_hsorted == nullptr) {
			assert(i == 0);
			p_hsorted = p_current;
			p_current->set_next(nullptr);
		} else if (i == 1) {
			assert(i == 1);
			if (*p_current < *p_hsorted) {
				p_current->set_next(p_hsorted);
				p_hsorted = p_current;
			} else {
				p_hsorted->set_next(p_current);
				p_current->set_next(nullptr);
			}
		} else {
			assert(i > 1);
			for (std::size_t k{0}; k < i; ++k){
				if (k == 0) {
					if (*p_current < *p_hsorted) {
						p_current->set_next(p_hsorted);
						p_hsorted = p_current;
						break;
					}
					p_csorted = p_hsorted;
					p_bsorted = p_hsorted;
				} else {
					if (*p_current < *p_csorted){
						p_current->set_next(p_csorted);
						p_bsorted->set_next(p_current);
						break;
					} else {
						if (p_csorted->get_next() == nullptr) {
							p_current->set_next(nullptr);
							p_csorted->set_next(p_current);
						}
					}
				}
				p_bsorted = p_csorted;
				if (k != i - 1) {
					p_csorted = p_csorted->get_next();
				}
			}
		}
		ncount++;
	}
	assert(ncount == count);
	p_head = p_hsorted;
}

// TASK
// update_acb_cgl(): Updates the ACB and CGL values. 
//

void History::update_acb_cgl() {
	std::size_t count{0};
	double total_acb{0.0};
	unsigned int total_shares{0};
	double acb_p_share{0.0};
	double total_cgl{0.0};
	Transaction *temp{p_head};

	for (Transaction *p_current_node{p_head}; p_current_node != nullptr; p_current_node = p_current_node->get_next()) {
		count++;
	}

	for (std::size_t i{0}; i < count; ++i) {
		total_cgl = 0;
		if (temp->get_trans_type()) {
			total_acb += temp->get_amount();
			total_shares += temp->get_shares();
			acb_p_share = total_acb / total_shares;
		} else {
			total_shares -= temp->get_shares();
			total_acb -= temp->get_shares() * acb_p_share;
			total_cgl = temp->get_amount() - (temp->get_shares() * acb_p_share);
		}

		temp->set_acb(total_acb);
		temp->set_acb_per_share(acb_p_share);
		temp->set_share_balance(total_shares);
		temp->set_cgl(total_cgl);

		temp = temp->get_next();
	}
}

// TASK
// compute_cgl(): )Compute the ACB, and CGL.
//

double History::compute_cgl(unsigned int year) {
	std::size_t count{0};
	double cgl{0};
	unsigned int low{year * 1000}, high{(year + 1) * 1000 - 1};
	unsigned int current{0};
	Transaction *temp{p_head};

	for (Transaction *p_current_node{p_head}; p_current_node != nullptr; p_current_node = p_current_node->get_next()) {
		count++;
	}

	for (std::size_t i{0}; i < count ; ++i) {
		current = temp->get_day() + 50 * temp->get_month() + 1000 * temp->get_year();

		if (current < high && current > low) {
			cgl += temp->get_cgl();
		}

		temp = temp->get_next();
	}

	return cgl;
}


// TASK
// print() Print the transaction history.
//

void History::print() {
	std::size_t count{0};
	Transaction *temp{p_head};

	for (Transaction *p_current_node{temp}; p_current_node != nullptr; p_current_node = p_current_node->get_next()) {
		count++;
	}

	for (std::size_t i{0}; i < count ; ++i) {
		temp->print();
		temp = temp->get_next();
	}
}


// GIVEN
// get_p_head(): Full access to the linked list.
// 

Transaction *History::get_p_head() { return p_head; }

#endif

