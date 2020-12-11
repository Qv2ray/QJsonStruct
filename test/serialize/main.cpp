#include "QJsonStruct.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

const static inline auto INT_TEST_MAX = std::numeric_limits<int>::max() - 1;
const static inline auto INT_TEST_MIN = -(std::numeric_limits<int>::min() + 1);

#define SINGLE_ELEMENT_CLASS_DECL(CLASS, TYPE, field, defaultvalue)                                                                                  \
    class CLASS                                                                                                                                      \
    {                                                                                                                                                \
      public:                                                                                                                                        \
        TYPE field = defaultvalue;                                                                                                                   \
        JSONSTRUCT_REGISTER(CLASS, F(field));                                                                                                        \
    };

// SINGLE_ELEMENT_REQUIRE( CLASS_NAME , TYPE , FIELD , DEFAULT_VALUE , SET VALUE , CHECK VALUE )
#define SINGLE_ELEMENT_REQUIRE(CLASS, TYPE, field, defaultvalue, value, checkvalue)                                                                  \
    SINGLE_ELEMENT_CLASS_DECL(CLASS, TYPE, field, defaultvalue) CLASS CLASS##_class;                                                                 \
    CLASS##_class.field = value;                                                                                                                     \
    REQUIRE(CLASS##_class.toJson()[#field] == checkvalue);

using namespace std;
SCENARIO("Test Serialization", "[Serialize]")
{
    GIVEN("Single Element")
    {
        const static QList<QString> defaultList{ "entry 1", "entry 2" };
        const static QMap<QString, QString> defaultMap{ { "key1", "value1" }, { "key2", "value2" } };
        typedef QMap<QString, QString> QStringQStringMap;

        WHEN("Serialize a single element")
        {
            const static QStringQStringMap setValueMap{ { "newkey1", "newvalue1" } };
            const static QJsonObject setValueJson{ { "newkey1", QJsonValue{ "newvalue1" } } };

            SINGLE_ELEMENT_REQUIRE(QStringTest_Empty, QString, a, "empty", "", "");
            SINGLE_ELEMENT_REQUIRE(QStringTest, QString, a, "empty", "Some QString", "Some QString");
            SINGLE_ELEMENT_REQUIRE(QStringTest_WithQoutes, QString, a, "empty", "\"", "\"");
            SINGLE_ELEMENT_REQUIRE(QStringTest_zint, int, a, -10, 0, 0);
            SINGLE_ELEMENT_REQUIRE(QStringTest_nint, int, a, -10, 1, 1);
            SINGLE_ELEMENT_REQUIRE(QStringTest_pint, int, a, -10, -1, -1);
            SINGLE_ELEMENT_REQUIRE(QStringTest_pmint, int, a, -1, INT_TEST_MAX, INT_TEST_MAX);
            SINGLE_ELEMENT_REQUIRE(QStringTest_zmint, int, a, -1, INT_TEST_MIN, INT_TEST_MIN);
            SINGLE_ELEMENT_REQUIRE(QStringTest_zuint, uint, a, -10, 0, 0);
            SINGLE_ELEMENT_REQUIRE(QStringTest_puint, uint, a, -10, 1, 1);
            SINGLE_ELEMENT_REQUIRE(BoolTest_True, bool, a, false, true, true);
            SINGLE_ELEMENT_REQUIRE(BoolTest_False, bool, a, true, false, false);
            SINGLE_ELEMENT_REQUIRE(StdStringTest, string, a, "def", "std::string _test", "std::string _test");
            SINGLE_ELEMENT_REQUIRE(QListTest, QList<QString>, a, defaultList, { "newEntry" }, QJsonArray{ "newEntry" });
            SINGLE_ELEMENT_REQUIRE(QMapTest, QStringQStringMap, a, defaultMap, {}, QJsonObject{});
            SINGLE_ELEMENT_REQUIRE(QMapValueTest, QStringQStringMap, a, defaultMap, setValueMap, setValueJson);
        }

        WHEN("Serialize a default value")
        {
            SINGLE_ELEMENT_REQUIRE(DefaultQString, QString, a, "defaultvalue", "defaultvalue", QJsonValue::Undefined);
            SINGLE_ELEMENT_REQUIRE(DefaultInteger, int, a, 12345, 12345, QJsonValue::Undefined);
            SINGLE_ELEMENT_REQUIRE(DefaultList, QList<QString>, a, defaultList, defaultList, QJsonValue::Undefined);
            SINGLE_ELEMENT_REQUIRE(DefaultMap, QStringQStringMap, a, defaultMap, defaultMap, QJsonValue::Undefined);
        }
    }
}
