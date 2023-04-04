
#ifndef DOWNLOADMANAGER_APPLICATION_H
#define DOWNLOADMANAGER_APPLICATION_H




namespace core {

    class Application {
    public:
        Application() = default;
        ~Application() = default;

        //initialize sub system functions
        bool Init();

        //run the whole application loop
        void Run();

    private:

    };

}



#endif //DOWNLOADMANAGER_APPLICATION_H
