class Trigger {
public:
    virtual ~Trigger() {}
    virtual bool switch_pushed() = 0;
};

