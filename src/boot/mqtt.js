import { boot } from 'quasar/wrappers'
import { createPahoMqttPlugin } from 'vue-paho-mqtt'

// "async" is optional;
// more info on params: https://v2.quasar.dev/quasar-cli/boot-files
export default boot(({ app }) => {
  // something to do
  console.log('mqtt boot file')
  app.use(createPahoMqttPlugin({
    PluginOptions: {
      autoConnect: true,
      showNotifications: true
    },
    MqttOptions: {
      host: 'localhost',
      port: 9001,
      clientId: 'Consola1',
      mainTopic: 'BAILE'
    }
  }))
})
