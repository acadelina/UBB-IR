import React from 'react';
import { View, Text, StyleSheet } from 'react-native';

export default function App() {
    return (
        <View style={styles.container}>
            <Text style={styles.title}>Salut, React Native Web!</Text>
        </View>
    );
}

const styles = StyleSheet.create({
    container: {
        marginTop: 50,
        alignItems: 'center',
    },
    title: {
        fontSize: 24,
    },
});
