# Make a variations config files



index_mutat = 3
index_cross = 0
genetic = 1

arquivos = []

for k in range(2):
	genetic = k
	for j in range(17):
		index_cross = j
		for i in range(17):
			index_mutat = i

			texto = []
			texto.append('<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>')
			texto.append('<configuracaoTSP>')
			texto.append('\t<name>tspconfig</name>')
			texto.append('\t<source>TSPLIB</source>')
			texto.append('\t<description>Configuração da programa de Algoritmo Genético</description>')
			texto.append('\t\t <integer>15</integer>')
			texto.append('\t\t <printParcial>1</printParcial>')
			texto.append('\t\t <tamanhoPopulacao>30</tamanhoPopulacao>')
			texto.append('\t\t <numGeracoes>50</numGeracoes>')
			texto.append('\t\t <percentManipulacao>30</percentManipulacao>')
			texto.append('\t\t <percentMutacao>20</percentMutacao>')
			texto.append('\t\t <percentReducao>77</percentReducao>')
			texto.append('\t\t <mutacao>'+str(index_mutat)+'</mutacao>')
			texto.append('\t\t <selIndMutacao>1</selIndMutacao>')
			texto.append('\t\t <cruzamento>'+str(index_cross)+'</cruzamento>')
			texto.append('\t\t <numExec>1</numExec>')
			texto.append('\t\t <roleta>0</roleta>')
			texto.append('\t\t <percentElitismo>70</percentElitismo>')
			texto.append('\t\t <ativaRecursivo>'+str(genetic)+'</ativaRecursivo>')
			texto.append('</configuracaoTSP>')

			filename = 'tspconfig_m'+str(index_mutat)+'_c'+str(index_cross)+'_g'+str(genetic)+'.xml'
			arquivos.append(filename)
			arq = open('config/'+filename,'w')
			print('Gerando arquivo: '+'tspconfig_m'+str(index_mutat)+'_c'+str(index_cross)+'_g'+str(genetic)+'.xml')
			for txt in texto:
				arq.write(txt)
				arq.write('\n')
				#print(txt)
			arq.close()

# Gerando script de execução dos arquivos
print('Gerando arquivos com nomes para script: script/sh_names.txt')
arq = open('script/sh_names.txt','w')
for filename in arquivos:
	arq.write(filename)
	arq.write('\n')
arq.close()
