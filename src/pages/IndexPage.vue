<!-- eslint-disable no-unreachable -->
<!-- eslint-disable no-unreachable -->
<!-- eslint-disable no-unreachable -->
<template>
  <q-page class="q-ma-md">
    <div class="row q-ma-md">
      <div class="col-4">
        <div class="text-h6 inline">Generacion de Aleatorio</div>

        <div class="row">
          <div class="col-4">
            <div class="caption">Numero de leds</div>
            <q-input
              v-model.number="numPasos"
              type="number"
              filled
              style="max-width: 100px"
            />
          </div>
          <div class="col-4">
            <div class="caption">Delay del tiempo</div>
            <q-input
              v-model.number="delay"
              type="number"
              filled
              style="max-width: 100px"
            />
          </div>

          <div class="col-4 q-mt-lg">
            <q-btn label="Iniciar" color="primary" @click="generarAleatorio" />
          </div>
        </div>
        <div class="row q-my-md">
          <div class="col-3">
            <q-btn
              size="sm"
              label="Poner offline"
              color="primary"
              @click="ponerOffline"
            />
          </div>
          <div class="col-4">
            <q-toggle v-model="modoDark" label="Modo Oscuro" @click="cambiarModoOscuro" />
          </div>
        </div>
        <div class="row">
          <div class="col-4" >
            Música <br />
            <q-btn size="sm" icon="play_arrow" color="green" @click="cancion.play()" />
            <q-btn size="sm" icon="pause" color="green" @click="cancion.pause()" />

          </div>
          <div class="col-3">MQTT: {{ statusMqtt }}</div>

        </div>
        <!-- Fila de la consola de mensajes, mostramos un control con scroll que muestra las colamensajes -->
        <div class="row">
          <div class="col-10">
            <div class="text-h6 inline">Consola de mensajes</div>
            <q-card class="my-card q-ma-none">
              <q-card-section  >
                <q-scroll-area style="height: 300px" class="q-ma-none">
                  <q-list  dense>
                    <q-item  class="q-ma-none"
                      v-for="(mensaje, index) in colaMensajesOrdenados"
                      :key="index"
                    >
                      <q-item-section >{{ mensaje }}</q-item-section>
                    </q-item>
                  </q-list>
                </q-scroll-area>
              </q-card-section>
            </q-card>
          </div>
        </div>
      </div>

      <div class="col-8">
        <div class="text-h6 inline">Resultados</div>
        <div class="q-pa-md row items-start q-gutter-md">
          <q-card
            class="my-card q-mt-lg"
            v-for="(equipo, index) in equiposOrdenados"
            :key="index"
          >
            <q-card-section class="bg-primary text-white">
              <div class="text-h4 q-ma-md">{{ equipo.nombre }}</div>
            </q-card-section>

            <q-separator />

            <q-card-actions align="around">
              <q-btn round size="xs" color="green" v-show="equipo.online"></q-btn>
              <div class="text-h3">{{ equipo.puntos }}</div>
            </q-card-actions>
          </q-card>
        </div>
      </div>
    </div>
  </q-page>
</template>

<script setup>
import { ref, computed, onMounted } from 'vue'
import { useQuasar } from 'quasar'
import { $mqtt } from 'vue-paho-mqtt'

const $q = useQuasar()
const colaMensajes = ref([])
const colaMensajesOrdenados = computed(() => [...colaMensajes.value].reverse())
const numPasos = ref(60)
const delay = ref(500)
const cancion = new Audio('captainJack.mp3')
const equipos = ref([
  { nombre: 'BOBESPONJA', puntos: 0, online: true },
  { nombre: 'PATRICIO', puntos: 0, online: true },
  { nombre: 'CALAMARDO', puntos: 0, online: true },
  { nombre: 'GARY', puntos: 0, online: true },
  { nombre: 'DONCANGREJO', puntos: 0, online: true },
  { nombre: 'ARENITA', puntos: 0, online: true },
  { nombre: 'PLANKTON', puntos: 0, online: true }
])

// propiedad computada de equipos ordenados
const equiposOrdenados = computed(() => {
  return [...equipos.value].sort((a, b) => b.puntos - a.puntos)
})
const modoDark = computed(() => {
  return $q.dark.isActive
})
const statusMqtt = computed(() => {
  return $mqtt.status()
})

function generarAleatorio () {
  // en base al numero de pasos genero esa cantidad de valores aleatorios
  // los valores aleatorios son: L, R, U y D
  // y lo guardamos en una cadena
  let cadena = ''
  for (let i = 0; i < numPasos.value - 1; i++) {
    cadena += 'R'
  }
  const pos = Math.floor(Math.random() * (numPasos.value - 2))
  cadena = cadena.split('')
  cadena[pos] = 'V'
  cadena[pos + 1] = 'V'
  // pos = Math.floor(Math.random() * numPasos.value - 1)
  cadena = cadena.join('')
  console.log(delay.value + ',' + cadena)
  $mqtt.publish('BAILE', delay.value + ',' + cadena, 'Qr')
  colaMensajes.value.push(delay.value + ',' + cadena)
}

function ponerOffline () {
  equipos.value.forEach((equipo) => {
    equipo.online = false
  })
}

function cambiarModoOscuro () {
  $q.dark.set(!modoDark.value)
}

onMounted(() => {
  console.log('estoy aqui')
  setTimeout(() => {
    console.log($mqtt.status())
    if ($mqtt.status() === 'connected') {
      console.log('me suscribo a BAILE/EQUIPOS')
      $mqtt.subscribe('EQUIPOS', (message) => {
        console.log('mensaje recibido ' + message)
        const mensaje = message.toString().toUpperCase()
        console.log(mensaje)
        procesarMensaje(mensaje)
      })
    }
  }, 3000)
})

function procesarMensaje (mensaje) {
  try {
    colaMensajes.value.push(mensaje)
    if (mensaje.includes(',')) {
      console.log('incluye coma')
      const [nombre, puntos] = mensaje.split(',')
      const equipo = equipos.value.find((equipo) => equipo.nombre.toUpperCase() === nombre)
      if (equipo) {
        if (puntos !== undefined && puntos !== null) {
          equipo.puntos += parseInt(puntos)
          equipo.online = true
        }
      }
    } else {
      console.log('no incluye coma')
      const equipo = equipos.value.find((equipo) => equipo.nombre.toUpperCase() === mensaje)
      if (equipo) {
        equipo.online = true
      }
    }
  } catch (error) {
    console.log('Error al procesar mensaje')
    console.log(mensaje)
    console.log(error)
  }
}
</script>
