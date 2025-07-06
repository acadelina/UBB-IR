import {Dimensions, LayoutChangeEvent, ScrollView, Text, View} from "react-native";
import {useState} from "react";


const { height, width } = Dimensions.get("window");

const tableHeaders = [
    { key: "id", name: "ID", style: { width: width * 0.145, marginLeft: width * 0.016 } },
    { key: "artist", name: "ARTIST", style: { width: width * 0.21 } },
    { key: "locatie", name: "LOCATIE", style: { width: width * 0.11 } },
    { key: "data", name: "DATA", style: { width: width * 0.22 } },
    { key: "avseats", name: "L. DISPONIBILE", style: { width: width * 0.19 } },
    { key: "soseats", name: "L. VANDUTE", style: { width: width * 0.19 } },
];

export default function TabelSpectacole({ spectacole }) {
    const [rowHeights, setRowHeights] = useState({});

    const handleTextLayout = (index: number, event: LayoutChangeEvent) => {
        const height = event.nativeEvent.layout.height;
        setRowHeights((prevHeights) => ({
            ...prevHeights,
            [index]: Math.max(prevHeights[index] || 0, height),
        }));
    };

    return (
        <View style={{ alignItems: "center", paddingTop: height * 0.01, paddingHorizontal: width * 0.01 }}>
            <View
                style={{
                    backgroundColor: "rgba(174,185,196,0.49)",
                    borderStyle: "solid",
                    borderColor: "#AEB9C4",
                    borderWidth: 0.5,
                    height: height * 0.6,
                    width: width * 0.95,
                    borderRadius: 10,
                    boxShadow: `0px ${height * 0.01} ${height * 0.02} #02407315`,
                    overflow: "hidden",
                }}>

                <View>
                    <View
                        style={{
                            flexDirection: "row",
                            backgroundColor: "#AEB9C4",
                            borderRadius: 10,
                            height: height * 0.045,
                            paddingRight: width * 0.02,
                        }}>
                        {tableHeaders.map((header, index) => (
                            <View
                                key={index}
                                style={[
                                    {
                                        height: height * 0.03,
                                        borderRadius: 5,
                                        alignSelf: "center",
                                        alignItems: "center",
                                        justifyContent: "center",
                                        marginLeft: width * 0.01,
                                        backgroundColor: '#024073'
                                    },
                                    header.style,
                                ]}>
                                <Text
                                    style={{
                                        fontSize: height * 0.014,
                                        fontFamily: "Montserrat",
                                        color: "#FFF",
                                        fontWeight: "500",
                                        justifyContent: "center",
                                        textAlignVertical: "center",
                                        textAlign: 'center'
                                    }}>
                                    {header.name}
                                </Text>
                            </View>
                        ))}
                    </View>

                    <ScrollView
                        contentContainerStyle={{
                            paddingBottom: height * 0.02,
                            alignItems: "flex-start",
                            justifyContent: "flex-start",
                        }}>
                        {spectacole.map((spectacol, index) => (
                            <View
                                key={index}
                                onLayout={(event) => handleTextLayout(index, event)}
                                style={{
                                    marginTop: height * 0.011,
                                    flexDirection: "row",
                                    alignItems: "center",
                                    minHeight: rowHeights[index] || height * 0.035,
                                }}>
                                {tableHeaders.map((header, colIndex) => (
                                    <View
                                        key={colIndex}
                                        style={[
                                            {
                                                backgroundColor: "#fff",
                                                borderRadius: 5,
                                                justifyContent: "center",
                                                alignItems: "center",
                                                marginLeft: width * 0.01,
                                            },
                                            header.style,
                                            { minHeight: rowHeights[index] || height * 0.035 },
                                        ]}>
                                        <Text>
                                            {spectacol[header.key]}
                                        </Text>
                                    </View>
                                ))}
                            </View>
                        ))}
                    </ScrollView>
                </View>

            </View>
        </View>
    );
}
