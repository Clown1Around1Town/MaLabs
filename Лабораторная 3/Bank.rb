require 'thread'

class BankAccount
    attr_accessor :balance

    def initialize(balance = 0)
        @balance = balance
        @mutex = Mutex.new
    end

    def deposit(amount)
        @mutex.synchronize do
            @balance += amount
            puts "Deposited #{amount}, new balance is #{@balance}"
        end
    end

    def withdraw(amount)
        @mutex.synchronize do
            if @balance >= amount
                @balance -= amount
                puts "Withdrew #{amount}, new balance is #{@balance}"
            else
                puts "Insufficient funds for withdrawal of #{amount}, current balance is #{@balance}"
            end
        end
    end
end

account = BankAccount.new(100)

threads = []

5.times do |i|
    threads << Thread.new do
        10.times do
            account.deposit(10 * (i + 1))
            sleep(rand(0.01..0.1))
        end
    end

    threads << Thread.new do
        10.times do
            account.withdraw(5 * (i + 1))
            sleep(rand(0.01..0.1))
        end
    end
end

threads.each(&:join)

puts "Final balance is #{account.balance}"