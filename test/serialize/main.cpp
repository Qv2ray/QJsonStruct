#include "QJsonStruct.hpp"

#include <QObject>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

const static inline auto INT_TEST_MAX = std::numeric_limits<int>::max() - 1;
const static inline auto INT_TEST_MIN = -(std::numeric_limits<int>::min() + 1);

#define EXT_O
#define EXT_
#define EXT_F REQUIRED
#define EXT(x) EXT_##x

#define SINGLE_ELEMENT_CLASS_DECL(CLASS, TYPE, field, defaultvalue)                                                                                  \
    class CLASS                                                                                                                                      \
    {                                                                                                                                                \
                                                                                                                                                     \
      public:                                                                                                                                        \
        TYPE field = defaultvalue;                                                                                                                   \
        QJS_PLAIN_JSON(field);                                                                                                                       \
    };

// SINGLE_ELEMENT_REQUIRE( CLASS_NAME , TYPE , FIELD , DEFAULT_VALUE , SET VALUE , CHECK VALUE )
#define SINGLE_ELEMENT_REQUIRE(CLASS, TYPE, field, defaultvalue, value, checkvalue)                                                                  \
    SINGLE_ELEMENT_CLASS_DECL(CLASS, TYPE, field, defaultvalue)                                                                                      \
    CLASS CLASS##_class;                                                                                                                             \
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

            SINGLE_ELEMENT_CLASS_DECL(QStringTest_Empty, QString, a, "empty")
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

        //        WHEN("Serialize a default value")
        //        {
        //            SINGLE_ELEMENT_REQUIRE(DefaultQString, QString, a, "defaultvalue", "defaultvalue", QJsonValue::Undefined);
        //            SINGLE_ELEMENT_REQUIRE(DefaultInteger, int, a, 12345, 12345, QJsonValue::Undefined);
        //            SINGLE_ELEMENT_REQUIRE(DefaultList, QList<QString>, a, defaultList, defaultList, QJsonValue::Undefined);
        //            SINGLE_ELEMENT_REQUIRE(DefaultMap, QStringQStringMap, a, defaultMap, defaultMap, QJsonValue::Undefined);
        //        }

        WHEN("Serialize a force existance default value")
        {
            const static QJsonArray defaultListJson{ "entry 1", "entry 2" };
            const static QJsonObject defaultMapJson{ { "key1", "value1" }, { "key2", "value2" } };
            SINGLE_ELEMENT_REQUIRE(DefaultQString, QString, a, "defaultvalue", "defaultvalue", "defaultvalue");
            SINGLE_ELEMENT_REQUIRE(DefaultInteger, int, a, 12345, 12345, 12345);
            SINGLE_ELEMENT_REQUIRE(DefaultList, QList<QString>, a, defaultList, defaultList, defaultListJson);
            SINGLE_ELEMENT_REQUIRE(DefaultMap, QStringQStringMap, a, defaultMap, defaultMap, defaultMapJson);
        }
    }

    GIVEN("Multiple Simple Elements")
    {
        //        WHEN("Can Omit Default Value")
        //        {
        //            class MultipleNonDefaultElementTestClass
        //            {
        //              public:
        //                QString astring;
        //                int integer = 0;
        //                double adouble = 0.0;
        //                QList<QString> myList;
        //                QJS_PLAIN_JSON(astring, integer, adouble, myList)
        //            };
        //            MultipleNonDefaultElementTestClass instance;
        //            const auto json = instance.toJson();
        //            REQUIRE(json["astring"] == QJsonValue::Undefined);
        //            REQUIRE(json["integer"] == QJsonValue::Undefined);
        //            REQUIRE(json["adouble"] == QJsonValue::Undefined);
        //            REQUIRE(json["myList"] == QJsonValue::Undefined);
        //        }

        WHEN("Forcing Existance")
        {
            class MultipleNonDefaultExistanceElementTestClass
            {
              public:
                QString astring;
                int integer = 0;
                double adouble = 0.0;
                QList<QString> myList;
                QJS_PLAIN_JSON(astring, integer, adouble, myList)
            };
            MultipleNonDefaultExistanceElementTestClass instance;
            const auto json = instance.toJson();
            REQUIRE(json["astring"] == "");
            REQUIRE(json["integer"] == 0);
            REQUIRE(json["adouble"] == 0.0);
            REQUIRE(json["myList"] == QJsonArray{});
        }
    }

    GIVEN("Nested Elements")
    {
        //        WHEN("Can Omit Default Value")
        //        {
        //            class Parent
        //            {
        //                class NestedChild
        //                {
        //                    class NestedChild2
        //                    {
        //                      public:
        //                        int childChildInt = 13579;
        //                        QJS_PLAIN_JSON(childChildInt)
        //                    };

        //                  public:
        //                    int childInt = 54321;
        //                    QString childQString = "A QString";
        //                    NestedChild2 anotherChild;
        //                    QJS_PLAIN_JSON(childInt, childQString, anotherChild)
        //                };

        //              public:
        //                int parentInt = 12345;
        //                NestedChild child;
        //                QJS_PLAIN_JSON(parentInt, child)
        //            };

        //            WHEN("Omitted whole child element")
        //            {
        //                Parent parent;
        //                const auto json = parent.toJson();
        //                REQUIRE(json["parentInt"] == QJsonValue::Undefined);
        //                REQUIRE(json["child"] == QJsonValue::Undefined);
        //            }

        //            WHEN("Omitted one element in the child")
        //            {
        //                const auto childJson = QJsonObject{ { "childInt", 1314 } };
        //                Parent parent;
        //                parent.child.childInt = 1314;
        //                const auto json = parent.toJson();
        //                REQUIRE(json["parentInt"] == QJsonValue::Undefined);
        //                REQUIRE(json["child"] == childJson);
        //                REQUIRE(json["child"]["childInt"] == 1314);
        //                REQUIRE(json["child"]["childQString"] == QJsonValue::Undefined);
        //                REQUIRE(json["child"]["child"]["anotherChild"] == QJsonValue::Undefined);
        //            }

        //            WHEN("Omitted one element in the child child")
        //            {
        //                Parent parent;
        //                parent.child.childInt = 1314;
        //                parent.child.anotherChild.childChildInt = 97531;
        //                const auto json = parent.toJson();
        //                REQUIRE(json["parentInt"] == QJsonValue::Undefined);
        //                REQUIRE(json["child"]["childInt"] == 1314);
        //                REQUIRE(json["child"]["childQString"] == QJsonValue::Undefined);
        //                const QJsonObject childChild{ { "childChildInt", 97531 } };
        //                REQUIRE(json["child"]["anotherChild"] == childChild);
        //                REQUIRE(json["child"]["anotherChild"]["childChildInt"] == 97531);
        //            }
        //        }
    }
}
