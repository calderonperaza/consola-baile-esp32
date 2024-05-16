<template>
  <q-page class="q-ma-md">
    <div class="row q-ma-md">
      <div class="col-4">
        <div class="text-h6 inline">Generacion de Aleatorio</div>

        <div class="row">
          <div class="col-4">
            <div class="caption">Numero de pasos</div>
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
          <div class="col-3">
            <q-btn size="sm" icon="play_arrow" color="green" @click="cancion.play()" />
            <q-btn size="sm" icon="pause" color="green" @click="cancion.pause()" />
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

const numPasos = ref(10)
const delay = ref(1000)
const cancion = new Audio('captainJack.mp3')
const equipos = ref([
  { nombre: 'Namekusei', puntos: 0, online: true },
  { nombre: 'Androides', puntos: 4, online: true },
  { nombre: 'Ginyu', puntos: 0, online: true },
  { nombre: 'Dabura', puntos: 0, online: true },
  { nombre: 'Tao Pai Pai', puntos: 126, online: true },
  { nombre: 'Yamcha', puntos: 0, online: true },
  { nombre: 'Patrulla Roja', puntos: 0, online: true },
  { nombre: 'Spopovich', puntos: 9, online: true },
  { nombre: 'Yamu', puntos: 0, online: true }
])

// propiedad computada de equipos ordenados
const equiposOrdenados = computed(() => {
  return [...equipos.value].sort((a, b) => b.puntos - a.puntos)
})
const modoDark = computed(() => {
  return $q.dark.isActive
})

function generarAleatorio () {
  // en base al numero de pasos genero esa cantidad de valores aleatorios
  // los valores aleatorios son: L, R, U y D
  // y lo guardamos en una cadena
  let cadena = ''
  for (let i = 0; i < numPasos.value; i++) {
    const aleatorio = Math.floor(Math.random() * 4)
    switch (aleatorio) {
      case 0:
        cadena += 'L'
        break
      case 1:
        cadena += 'R'
        break
      case 2:
        cadena += 'U'
        break
      case 3:
        cadena += 'D'
        break
    }
  }
  console.log(delay.value + ',' + cadena)
  $mqtt.publish('BAILE', delay.value + ',' + cadena, 'Qr')
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
        //  console.log('mensaje')
        console.log(message)
      })
    }
  }, 3000)
})
</script>
