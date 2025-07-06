const path = require('path');

module.exports = {
    entry: './src/index.js',
    mode: 'development',
    resolve: {
        alias: {
            'react-native$': 'react-native-web',
        },
        extensions: ['.web.js', '.js'],
    },
    output: {
        filename: 'bundle.js',
        path: path.resolve(__dirname, 'dist'),
        publicPath: '/',
    },
    devServer: {
        static: './public',
        port: 3000,
        hot: true,
        open: true,
    },
    module: {
        rules: [
            {
                test: /\.(js|jsx|ts|tsx)$/,
                exclude: /node_modules/,
                use: 'babel-loader',
            },
        ],
    },
};
