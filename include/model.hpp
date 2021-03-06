#ifndef __MODEL_HPP__
#define __MODEL_HPP__


namespace dl {

  template <typename OutType>
  class Model {
  public:
    virtual ~Model() = 0;

    virtual std::vector<double> getCoefficients(void);
    virtual OutType predict(const std::vector<double>& features);

  };

  Model::~Model() = { }

    class Classifier: public Model<bool> {

      virtual ~Classifier() = 0;

      virtual std::vector<double> getProbabilities(const std::vector<double>& features);

    }
  




}

#endif // __MODEL_HPP__
