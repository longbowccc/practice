<?php


class HousePrice {
   
    private $net_price_ratio = 0.9;
    private $tariff_ratio = 0.015;
    private $commission_ratio = 0.027;
    private $loan_ratio = 0.7;
    private $price;
    private $is_economical_house = false;
    
    public function __construct($price, $is_economical_house) {
        $this->price = $price;
        $this->is_economical_house = $is_economical_house;
    }

    /*
    * calculation down payment
    */
    public function calculateDownPayment() {
        $net_price = $this->price * $this->net_price_ratio;
        $tariff = $net_price * $this->tariff_ratio;
        $commission = $this->price * $this->commission_ratio;
        $loan = $net_price * $this->loan_ratio;
        $land_price = $this->is_economical_house?$net_price*0.1:0;
        $total = $this->price + $tariff + $commission + $land_price;
        $down_payment = $total - $loan;
        echo "total:$total, down_payment:$down_payment, loan:$loan, tariff: $tariff, commission:$commission, land_pirce:$land_price\n";
    }

}

class Loan {
    private $base_rate = 0.049;
    private $discount = 0.85;
    private $loan_amount;
    private $years;

    public function __construct($amount, $years) {
        $this->loan_amount = $amount;
        $this->years = $years;
        if ($years <= 0) {
            throw new Exception("invalid years", 505);
        }
    }

    public function calculationMonthPayment($average_capital=false) {
        $rate = round($this->base_rate * $this->discount, 4);
        $month_rate = round($rate/12, 10);
        $loan_amount = $this->loan_amount;
        $months = 12 * $this->years;

        if ($average_capital) {
            /* 等额本金 */
            $month_pays = array();
            $month_capital = round($loan_amount/$months, 2);
            $returned_capital = 0;
            $total_interest = 0;
            for ($i=1;$i<=$months;$i++) {
                $interest = round(($loan_amount-$returned_capital)*$month_rate, 2);
                $month_pays []= $month_capital + $interest;
                echo "$month_capital+$interest\n";
                $total_interest += $interest;
                $returned_capital += $month_capital;
            }
            $total_pay = $total_interest + $pay;
            echo "total:$total_pay, monthly:\n";
            $month = 1;
            foreach ($month_pays as $month_pay) {
                echo "$month: $month_pay\n";
                $month++;
            }
        } else {
            /* 等额本息 */
            $month_roll_rate = pow(1+$month_rate, $months);
            $month_pay = $loan_amount * $month_rate * $month_roll_rate/($month_roll_rate-1);
            $total_pay = $month_pay * $months;
            $month_pay = round($month_pay, 2);
            $total_pay = round($total_pay, 2);
            echo "total:$total_pay, monthly:$month_pay*$months, rate:$rate month_rate:$month_rate, roll_rate:$month_roll_rate\n";
        }
    }
}

$h1 = new HousePrice(313, true);
#$h1->calculateDownPayment();
$loan = new Loan(1850000, 20);
$loan->calculationMonthPayment(false);

