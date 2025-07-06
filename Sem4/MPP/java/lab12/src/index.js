import { AppRegistry } from 'react-native';
import App from './App';
import appJson from './app.json';
const appName = appJson.name;
import { createRoot } from 'react-dom/client';

AppRegistry.registerComponent(appName, () => App);
AppRegistry.runApplication(appName, {
    rootTag: document.getElementById('root'),
});
