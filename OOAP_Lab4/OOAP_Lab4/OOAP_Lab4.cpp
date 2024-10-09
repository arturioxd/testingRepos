#include <iostream>
#include <memory>
#include <string>

class Phone {
public:
    void setModel(const std::string& model) {
        this->model = model;
    }

    void setPrice(double price) {
        this->price = price;
    }

    void setDeliveryTime(int days) {
        this->deliveryTime = days;
    }

    std::string getModel() const {
        return model;
    }

    double getPrice() const {
        return price;
    }

    int getDeliveryTime() const {
        return deliveryTime;
    }

private:
    std::string model;
    double price;
    int deliveryTime;
};

class PhoneBuilder {
public:
    virtual void buildModel() = 0;
    virtual void buildPrice() = 0;
    virtual void buildDeliveryTime() = 0;

    std::shared_ptr<Phone> getPhone() {
        return phone;
    }

    virtual ~PhoneBuilder() {}

protected:
    std::shared_ptr<Phone> phone = std::make_shared<Phone>();
};

class USAPhoneBuilder : public PhoneBuilder {
public:
    void buildModel() override {
        phone->setModel("Модель США");
    }

    void buildPrice() override {
        phone->setPrice(1000);
    }

    void buildDeliveryTime() override {
        phone->setDeliveryTime(7);
    }
};

class EastCountryPhoneBuilder : public PhoneBuilder {
public:
    void buildModel() override {
        phone->setModel("Модель сходу");
    }

    void buildPrice() override {
        phone->setPrice(700);
    }

    void buildDeliveryTime() override {
        phone->setDeliveryTime(14);
    }
};

class PhoneDirector {
public:
    void setBuilder(std::shared_ptr<PhoneBuilder> builder) {
        this->builder = builder;
    }

    std::shared_ptr<Phone> buildPhone() {
        builder->buildModel();
        builder->buildPrice();
        builder->buildDeliveryTime();
        return builder->getPhone();
    }

private:
    std::shared_ptr<PhoneBuilder> builder;
};

class OnlineStore {
public:
    OnlineStore(std::shared_ptr<PhoneDirector> director, std::shared_ptr<PhoneBuilder> builder)
        : director(director), builder(builder) {}

    void orderPhone() const {
        director->setBuilder(builder);
        auto phone = director->buildPhone();
        std::cout << "Модель: " << phone->getModel() << std::endl;
        std::cout << "Ціна: $" << phone->getPrice() << std::endl;
        std::cout << "Час доставки: " << phone->getDeliveryTime() << " днів" << std::endl;
    }

private:
    std::shared_ptr<PhoneDirector> director;
    std::shared_ptr<PhoneBuilder> builder;
};

int main() {
    setlocale(LC_ALL, "Ukrainian");
    int choice;
    std::cout << "Країна-виробник:\n1. США\n2. Країна сходу" << std::endl;
    std::cin >> choice;

    std::shared_ptr<PhoneBuilder> builder;
    std::shared_ptr<PhoneDirector> director = std::make_shared<PhoneDirector>();

    if (choice == 1) {
        builder = std::make_shared<USAPhoneBuilder>();
    }
    else if (choice == 2) {
        builder = std::make_shared<EastCountryPhoneBuilder>();
    }
    else {
        std::cout << "Неправильний вибір!" << std::endl;
        return 1;
    }

    OnlineStore store(director, builder);
    store.orderPhone();

    return 0;
}
